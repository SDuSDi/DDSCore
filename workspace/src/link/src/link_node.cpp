// ROS libraries and dependencies
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/empty.hpp"
#include "std_msgs/msg/float32.hpp"
#include "std_msgs/msg/int16.hpp"
#include "std_msgs/msg/bool.hpp"

// Own messages from core_msgs
#include "core_msgs/msg/aux_global_position.hpp"
#include "core_msgs/msg/StatusProvider.hpp"

// JSON library
#include <nlohmann/json.hpp>
using json = nlohmann::json; // for convenience

// MQTT files and setup
#include "listener.cpp"
#include "publisher.cpp"
mqtt::async_client *client = NULL;

class LinkNode : public rclcpp::Node
{
public:
    LinkNode(int argc, char **argv) : Node("linknode")
    {

        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        std::string	address  = (argc > 1) ? std::string(argv[1]) : publisher::DFLT_SERVER_ADDRESS,
		            clientID = (argc > 2) ? std::string(argv[2]) : publisher::CLIENT_ID;
        
        std::cout << "\nInitializing for server '" << address << "'..." << std::endl;
	    mqtt::async_client client(address, clientID, publisher::PERSIST_DIR);

    	publisher::callback cb;
	    client.set_callback(cb);

        auto connOpts = mqtt::connect_options_builder()
            .clean_session()
            .will(mqtt::message(publisher::TOPIC, publisher::LWT_PAYLOAD, strlen(publisher::LWT_PAYLOAD), publisher::QOS, false))
            .finalize();

        std::cout << "Everything OK. Starting..." << std::endl;

        // Connect
		std::cout << "\nConnecting...";
		mqtt::token_ptr conntok = client.connect(connOpts);
		std::cout << " OK" << std::endl << "Waiting for the connection...";
		conntok->wait();
		std::cout << " OK" << std::endl;

        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

        caller();
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

    void caller();

    void do_takeoff();
    void do_land();
    void gp_move();

};

void LinkNode::status_cb(const core_msgs::msg::StatusProvider::SharedPtr msg)
{
    publisher::action_listener listener;
    json tmp_msg = {
        {"id",msg -> id},
	    {"lat",msg -> lat},
	    {"lon",msg -> lon},
	    {"alt",msg -> alt},
	    {"arming_state",msg -> arming_state},
	    {"nav_state",msg -> nav_state},
    };
    std::string PAYLOAD = to_string(tmp_msg);
    mqtt::message_ptr pubmsg = mqtt::make_message(publisher::TOPIC, PAYLOAD);
    mqtt::delivery_token_ptr pubtok = client.publish(pubmsg, nullptr, listener);
    pubtok->wait();

    auto toks = client.get_pending_delivery_tokens();
    if (!toks.empty())
        std::cout << "Error: There are pending delivery tokens!" << std::endl;

    Disconnect
    std::cout << "\nDisconnecting...";
    client.disconnect()->wait();
    std::cout << " OK" << std::endl;
}

void LinkNode::caller()
{
    char* id = std::getenv("ROS_DOMAIN_ID");
    while(true)
    {
        if(listener::data["id"]==id){
            // std::cout<<"ID: "<<data["id"]<<" Domain ID: "<<id<<std::endl;
            if(listener::data["command"]=="takeoff"){do_takeoff();}
            if(listener::data["command"]=="land"){do_land();}
            if(listener::data["command"]=="move"){gp_move();}
            listener::data["id"]="-1"; listener::data["command"]=""; listener::data["param1"]=0; 
            listener::data["param2"]=0; listener::data["param3"]=0; listener::data["param4"]=0; listener::data["param5"]=0;
        }

    }
}

void LinkNode::do_takeoff()
{
    std_msgs::msg::Int16 mode;
    mode.data = 1;
    mode_pub -> publish(mode);
    arm_pub -> publish(std_msgs::msg::Empty());
    std_msgs::msg::Float32 msg;
    msg.data = listener::data["param1"];
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
    msg.speed = listener::data["param1"];
    msg.yaw = listener::data["param2"];
    msg.lat = listener::data["param3"];
    msg.lon = listener::data["param4"];
    msg.alt = listener::data["param5"];
    global_movement_pub -> publish(msg);
}

int main(int argc, char **argv){ //TODO: Revisar que esto de aqui esta mal

    rclcpp::init(argc, argv);

    client = new mqtt::async_client("127.0.0.1:1883", "Link-consumer", 0);
    mqtt::connect_options connOpts;
    connOpts.set_clean_session(false);
    listener::callback mqtt_cb(*client, connOpts);
    client->set_callback(mqtt_cb);
    client->start_consuming();
    client->connect(connOpts);

    rclcpp::spin(std::make_shared<LinkNode>(argc,argv));
    rclcpp::shutdown();

    return 0;
}