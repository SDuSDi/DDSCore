// ROS libraries and dependencies
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/empty.hpp"
#include "std_msgs/msg/float32.hpp"

// PX4 libraries and dependencies
#include "px4_msgs/srv/vehicle_command.hpp"
#include "px4_msgs/msg/vehicle_command.hpp"
#include "px4_msgs/msg/vehicle_command_ack.hpp"
#include "px4_msgs/msg/vehicle_global_position.hpp"

std::array<float,3> global_pos;

// Subnormal

class ControlNode : public rclcpp::Node
{
public:
    ControlNode() : Node("ddscore")
    {
        // Definition of quality of service for all subscribers
        rmw_qos_profile_t qos_profile = rmw_qos_profile_sensor_data;
        auto qos = rclcpp::QoS(rclcpp::QoSInitialization(qos_profile.history, 5), qos_profile);

        // Definition of service clients
        command_cl = this -> create_client<px4_msgs::srv::VehicleCommand>("/fmu/vehicle_command");

        // Definition of subscribers
        global_position_check = this -> create_subscription<px4_msgs::msg::VehicleGlobalPosition>("/fmu/out/vehicle_global_position",qos,
                                std::bind(&ControlNode::global_pos_cb, this, std::placeholders::_1));
        takeoff_srv = this -> create_subscription<std_msgs::msg::Float32>("/ddscore/takeoff",qos, 
                      std::bind(&ControlNode::set_takeoff, this, std::placeholders::_1));
        land_srv = this -> create_subscription<std_msgs::msg::Empty>("/ddscore/land",qos,
                   std::bind(&ControlNode::set_land, this, std::placeholders::_1));
    }

private:

    void global_pos_cb(px4_msgs::msg::VehicleGlobalPosition::SharedPtr msg);

    void cb_srv_command(const rclcpp::Client<px4_msgs::srv::VehicleCommand>::SharedFuture future);
    void publish_srv_command(uint16_t command, float alt = 0.0);

    void set_takeoff(const std_msgs::msg::Float32::SharedPtr msg);
    void set_land(const std_msgs::msg::Empty::SharedPtr msg);

    rclcpp::Client<px4_msgs::srv::VehicleCommand>::SharedPtr command_cl;

    rclcpp::Subscription<px4_msgs::msg::VehicleGlobalPosition>::SharedPtr global_position_check;
    rclcpp::Subscription<std_msgs::msg::Float32>::SharedPtr takeoff_srv;
    rclcpp::Subscription<std_msgs::msg::Empty>::SharedPtr land_srv;

};

void ControlNode::global_pos_cb(const px4_msgs::msg::VehicleGlobalPosition::SharedPtr msg) {
    global_pos[1] = msg -> lat; global_pos[2] = msg -> lon; global_pos[3] = msg -> alt;
}

void ControlNode::cb_srv_command(const rclcpp::Client<px4_msgs::srv::VehicleCommand>::SharedFuture future) {
    auto status = future.wait_for(std::chrono::seconds(1));
    if (status == std::future_status::ready) {
        RCLCPP_INFO(this -> get_logger(), 
        "\n\nCommand sent: "+std::to_string(future.get() -> reply.command)+"\nResult: "+std::to_string(future.get() -> reply.result)
        +"\nTarget System: "+std::to_string(future.get() -> reply.target_system)+"\nTarget Component: "+std::to_string(future.get() -> reply.target_component)
        +"\nExternal source: "+std::to_string(future.get() -> reply.from_external)+"\n");
    } else {
        RCLCPP_INFO(this -> get_logger(), "Service in progress");
    }
}

void ControlNode::publish_srv_command(uint16_t command, float alt) {
    
    auto request = std::make_shared<px4_msgs::srv::VehicleCommand::Request>();

    px4_msgs::msg::VehicleCommand msg{};

    msg.param5 = global_pos[1]; // Latitude
    msg.param6 = global_pos[2]; // Longitude

    // Absolute altitude + takeoff altitude
    if (command == 22) msg.param7 = global_pos[3] + alt;  //22 is the takeoff command
	else msg.param7 = global_pos[3]; 

	msg.command = command;
	msg.target_system = 1;
	msg.target_component = 1;
	msg.source_system = 1;
	msg.source_component = 1;
	msg.from_external = true;
    msg.timestamp = this -> get_clock() -> now().nanoseconds() / 1000;

    request -> request = msg;
    while(!command_cl -> wait_for_service(std::chrono::seconds(1)))
    {
        if (!rclcpp::ok()) {
            RCLCPP_ERROR(this -> get_logger(), "Interrupted while waiting for the service. Exiting...");
            return;
        }
        RCLCPP_INFO(this -> get_logger(), "Service not available. Waiting again...");
    }
    auto result = command_cl -> async_send_request(request, std::bind(&ControlNode::cb_srv_command, this, std::placeholders::_1));
}

void ControlNode::set_takeoff(const std_msgs::msg::Float32::SharedPtr msg) {
    RCLCPP_INFO(this -> get_logger(), "Hey! I'm going to take off!");
    publish_srv_command(px4_msgs::msg::VehicleCommand::VEHICLE_CMD_NAV_TAKEOFF, msg -> data);
}

void ControlNode::set_land(const std_msgs::msg::Empty::SharedPtr msg) {
    (void) msg; //Shuts the compiler up about the empty message not being used
    RCLCPP_INFO(this -> get_logger(), "Hey! I'm going to land!");
    publish_srv_command(px4_msgs::msg::VehicleCommand::VEHICLE_CMD_NAV_LAND);
}

int main(int argc, char **argv){

    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<ControlNode>());
    rclcpp::shutdown();

    return 0;

}