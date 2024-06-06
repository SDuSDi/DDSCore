// ROS libraries and dependencies
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/empty.hpp"
#include "std_msgs/msg/float32.hpp"
#include "std_msgs/msg/int16.hpp"
#include "std_msgs/msg/bool.hpp"

// Own messages from core_msgs
#include "core_msgs/msg/aux_global_position.hpp"

// JSON library
#include <nlohmann/json.hpp>
using json = nlohmann::json; // for convenience

// MQTT files and setup
#include "mqtt.cpp"
mqtt::async_client *client = NULL;

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
        caller();
    }
private:

    rclcpp::Publisher<std_msgs::msg::Int16>::SharedPtr mode_pub;
    rclcpp::Publisher<std_msgs::msg::Empty>::SharedPtr arm_pub;
    rclcpp::Publisher<std_msgs::msg::Empty>::SharedPtr disarm_pub;
    rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr takeoff_pub;
    rclcpp::Publisher<std_msgs::msg::Empty>::SharedPtr land_pub;
    rclcpp::Publisher<core_msgs::msg::AuxGlobalPosition>::SharedPtr global_movement_pub;

    void caller();

    void do_takeoff();
    void do_land();
    void gp_move();

};

void LinkNode::caller()
{
    char* id = std::getenv("ROS_DOMAIN_ID");
    while(true)
    {
        if(data["id"]==id){
            // std::cout<<"ID: "<<data["id"]<<" Domain ID: "<<id<<std::endl;
            if(data["command"]=="takeoff"){do_takeoff();}
            if(data["command"]=="land"){do_land();}
            if(data["command"]=="move"){gp_move();}
            data["id"]="-1"; data["command"]=""; data["param1"]=0; data["param2"]=0; data["param3"]=0; data["param4"]=0; data["param5"]=0;
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
    msg.data = data["param1"];
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
    msg.speed = data["param1"];
    msg.yaw = data["param2"];
    msg.lat = data["param3"];
    msg.lon = data["param4"];
    msg.alt = data["param5"];
    global_movement_pub -> publish(msg);
}

int main(int argc, char **argv){

    rclcpp::init(argc, argv);

    client = new mqtt::async_client("127.0.0.1:1883", "Link-consumer", 0);
    mqtt::connect_options connOpts;
    connOpts.set_clean_session(false);
    callback mqtt_cb(*client, connOpts);
    client->set_callback(mqtt_cb);
    client->start_consuming();
    client->connect(connOpts);

    rclcpp::spin(std::make_shared<LinkNode>());
    rclcpp::shutdown();

    return 0;
}