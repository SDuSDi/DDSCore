// ROS libraries and dependencies
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/empty.hpp"

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
    ControlNode() : Node("control_node")
    {
        // Definition of quality of service for all subscribers
        rmw_qos_profile_t qos_profile = rmw_qos_profile_sensor_data;
        auto qos = rclcpp::QoS(rclcpp::QoSInitialization(qos_profile.history, 5), qos_profile);

        takeoff_cl = node -> create_client<px4_msgs::srv::VehicleCommand>("/fmu/vehicle_command");

        // Definition of real subscribers
        global_position_check = node -> create_subscription<px4_msgs::msg::VehicleGlobalPosition>("/fmu/out/vehicle_global_position",qos,
        std::bind());
        takeoff_srv = node -> create_subscription<std_msgs::msg::Empty>("/ddscore/takeoff",qos, );
    }

private:

    void global_pos_cb(px4_msgs::msg::VehicleGlobalPosition::SharedPtr msg);
    void publish_takeoff(const std_msgs::msg::Empty::SharedPtr msg);

    rclcpp::Client<px4_msgs::srv::VehicleCommand>::SharedPtr takeoff_cl;

    rclcpp::Subscription<px4_msgs::msg::VehicleGlobalPosition>::SharedPtr global_position_check;
    rclcpp::Subscription<std_msgs::msg::Empty>::SharedPtr takeoff_srv;

};

void ControlNode::global_pos_cb(const px4_msgs::msg::VehicleGlobalPosition::SharedPtr msg) {
    global_pos[1] = msg -> lat; global_pos[2] = msg -> lon; global_pos[3] = msg -> alt;
}

void ControlNode::publish_takeoff(const std_msgs::msg::Empty::SharedPtr msg) {
    (void) msg; //Shuts the compiler up about the empty message not being used
    RCLCPP_INFO(this -> get_logger(), "Hey! I'm going to take off!");

    auto request = std::make_shared<px4_msgs::srv::VehicleCommand::Request>();

    px4_msgs::msg::VehicleCommand command{};

    command.param5 = global_pos[1]; // Latitude
    command.param6 = global_pos[2]; // Longitude
	command.param7 = global_pos[3]; // Absolute altitude + takeoff altitude

	command.command = px4_msgs::msg::VehicleCommand::VEHICLE_CMD_NAV_TAKEOFF;
	command.target_system = 1;
	command.target_component = 1;
	command.source_system = 1;
	command.source_component = 1;
	command.from_external = true;
    command.timestamp = this -> get_clock() -> now().nanoseconds() / 1000;

    request -> request = command;

}

int main(int argc, char **argv){

    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<ControlNode>());
    rclcpp::shutdown();
}