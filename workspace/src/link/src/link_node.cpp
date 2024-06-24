// ROS libraries and dependencies
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/empty.hpp"
#include "std_msgs/msg/float32.hpp"
#include "std_msgs/msg/int16.hpp"
#include "std_msgs/msg/bool.hpp"

// Own messages from core_msgs
#include "core_msgs/msg/aux_global_position.hpp"
#include "core_msgs/msg/status_provider.hpp"

// JSON library
#include <nlohmann/json.hpp>
using json = nlohmann::json; // for convenience

// MQTT files and setup
#include "mqtt.cpp"
mqtt::async_client *client = NULL;

int arm_state = 1;

class LinkNode : public rclcpp::Node
{
public:
    LinkNode() : Node("linknode")
    {
        mode_pub = this -> create_publisher<std_msgs::msg::Int16>("/ddscore/mode",10);
        arm_pub = this -> create_publisher<std_msgs::msg::Empty>("/ddscore/arm",10);
        disarm_pub = this -> create_publisher<std_msgs::msg::Empty>("/ddscore/disarm",10);
        takeoff_pub = this -> create_publisher<std_msgs::msg::Float32>("/ddscore/takeoff",10);
        land_pub = this -> create_publisher<std_msgs::msg::Empty>("/ddscore/land",10);
        global_movement_pub = this -> create_publisher<core_msgs::msg::AuxGlobalPosition>("/ddscore/global_position_controller",10);

        // Definition of quality of service for the subscriber
        rmw_qos_profile_t qos_profile = rmw_qos_profile_sensor_data;
        auto qos = rclcpp::QoS(rclcpp::QoSInitialization(qos_profile.history, 5), qos_profile);

        status_sub = this -> create_subscription<core_msgs::msg::StatusProvider>("/ddscore/status",qos,
                             std::bind(&LinkNode::status_cb, this, std::placeholders::_1));

		auto timer_callback = [this]() -> void {
            if(mqttlink::data["id"]==mqttlink::ros_id){
                if(mqttlink::data["command"]=="takeoff"){do_takeoff();}
                if(mqttlink::data["command"]=="land"){do_land();}
                if(mqttlink::data["command"]=="move"){gp_move();}
                mqttlink::data["id"]="-1"; mqttlink::data["command"]="none"; mqttlink::data["param1"]=0; 
                mqttlink::data["param2"]=0; mqttlink::data["param3"]=0; mqttlink::data["param4"]=0; mqttlink::data["param5"]=0;
            }
		};
		timer = this -> create_wall_timer(std::chrono::milliseconds(100), timer_callback);
    }

private:

    rclcpp::Publisher<std_msgs::msg::Int16>::SharedPtr mode_pub;
    rclcpp::Publisher<std_msgs::msg::Empty>::SharedPtr arm_pub;
    rclcpp::Publisher<std_msgs::msg::Empty>::SharedPtr disarm_pub;
    rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr takeoff_pub;
    rclcpp::Publisher<std_msgs::msg::Empty>::SharedPtr land_pub;
    rclcpp::Publisher<core_msgs::msg::AuxGlobalPosition>::SharedPtr global_movement_pub;

    rclcpp::Subscription<core_msgs::msg::StatusProvider>::SharedPtr status_sub;
    void status_cb(const core_msgs::msg::StatusProvider::SharedPtr msg);

    rclcpp::TimerBase::SharedPtr timer;

    void do_takeoff();
    void do_land();
    void gp_move();
};

void LinkNode::status_cb(const core_msgs::msg::StatusProvider::SharedPtr msg)
{
    mqttlink::action_listener listener("Status Listener");
    json tmp_msg = {
        {"recipient","-1"},
        {"id",mqttlink::ros_id},
	    {"lat",msg -> lat},
	    {"lon",msg -> lon},
	    {"alt",msg -> alt},
	    {"arming_state",msg -> arming_state},
	    {"nav_state",msg -> nav_state},
    };
    arm_state = msg -> arming_state;
    std::string PAYLOAD = to_string(tmp_msg);
    mqtt::message_ptr pubmsg = mqtt::make_message(mqttlink::TOPIC_PUB, PAYLOAD);
    mqtt::delivery_token_ptr pubtok = client->publish(pubmsg, nullptr, listener);
    pubtok->wait();

    auto toks = client->get_pending_delivery_tokens();
    if (!toks.empty())
        std::cout << "Error: There are pending delivery tokens!" << std::endl;
}

void LinkNode::do_takeoff()
{
    std_msgs::msg::Int16 mode;
    mode.data = 1;
    mode_pub -> publish(mode);
    rclcpp::sleep_for(std::chrono::seconds(1));
    for (int i = 0; i < 50; i++){
        if(arm_state == 1){
            arm_pub -> publish(std_msgs::msg::Empty());
            rclcpp::sleep_for(std::chrono::milliseconds(100));
        }
    }
    rclcpp::sleep_for(std::chrono::seconds(2));
    std_msgs::msg::Float32 msg;
    msg.data = mqttlink::data["param1"];
    takeoff_pub -> publish(msg);
}

void LinkNode::do_land()
{
    land_pub -> publish(std_msgs::msg::Empty());
    // disarm_pub -> publish(std_msgs::msg::Empty());
}

void LinkNode::gp_move()
{
    core_msgs::msg::AuxGlobalPosition msg{};
    msg.speed = mqttlink::data["param1"];
    msg.yaw = mqttlink::data["param2"];
    msg.lat = mqttlink::data["param3"];
    msg.lon = mqttlink::data["param4"];
    msg.alt = mqttlink::data["param5"];
    global_movement_pub -> publish(msg);
}

int main(int argc, char **argv){

    rclcpp::init(argc, argv);

    std::string	address  = (argc > 1) ? std::string(argv[1]) : mqttlink::SERVER_ADDRESS,
                clientID = (argc > 2) ? std::string(argv[2]) : mqttlink::CLIENT_ID;
    
    std::cout << "\nInitializing for server '" << address << "'..." << std::endl;
    client = new mqtt::async_client (address, clientID, 0, mqttlink::PERSIST_DIR); // async_client (const string &serverURI, const string &clientId, int maxBufferedMessages, const string &persistDir)

    mqtt::connect_options connOpts = mqtt::connect_options_builder()
        .clean_session()
        .will(mqtt::message(mqttlink::TOPIC_PUB, mqttlink::LWT_PAYLOAD, strlen(mqttlink::LWT_PAYLOAD), mqttlink::QOS, false))
        .finalize();

    std::cout << "\nInitializing setup...";
    mqttlink::callback mqtt_cb(*client, connOpts);
    client->set_callback(mqtt_cb);
    std::cout << " OK" << std::endl;
    client->start_consuming();

    std::cout << "\nConnecting...";
    mqtt::token_ptr conntok = client->connect(connOpts);
    std::cout << " OK" << std::endl;
    conntok->wait();
    std::cout << "Waiting for the connection... OK" << std::endl;

    std::cout << "Everything OK. Starting..." << std::endl;

    rclcpp::spin(std::make_shared<LinkNode>());
    rclcpp::shutdown();

    return 0;
}