// Libraries and dependencies
#include "rclcpp/rclcpp.hpp"

// Message libraries
#include "std_msgs/msg/int16.hpp"
#include "std_msgs/msg/empty.hpp"
#include "std_msgs/msg/float32.hpp"
#include "core_msgs/msg/trajectory.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "core_msgs/msg/aux_global_position.hpp"

int main(int argc, char **argv){

    rclcpp::init(argc, argv);
    std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("test_case");
    RCLCPP_INFO(node -> get_logger(), "Start of test case");

    rclcpp::Publisher<std_msgs::msg::Int16>::SharedPtr mode_pub = node -> create_publisher<std_msgs::msg::Int16>("/ddscore/mode",10);
    std_msgs::msg::Int16 mode_msg{};
    mode_msg.data = 1;
    RCLCPP_INFO(node -> get_logger(), "Sending request to change mode to: %d", mode_msg.data);
    mode_pub -> publish(mode_msg);
    std::this_thread::sleep_for(std::chrono::seconds(2));

    rclcpp::Publisher<std_msgs::msg::Empty>::SharedPtr arm_pub = node -> create_publisher<std_msgs::msg::Empty>("/ddscore/arm",10);
    RCLCPP_INFO(node -> get_logger(), "Sending arming request");
    arm_pub -> publish(std_msgs::msg::Empty());
    std::this_thread::sleep_for(std::chrono::seconds(3));

    rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr takeoff_pub = node -> create_publisher<std_msgs::msg::Float32>("/ddscore/takeoff",10);
    std_msgs::msg::Float32 takeoff_msg{};
    takeoff_msg.data = 2.0;
    RCLCPP_INFO(node -> get_logger(), "Sending takeoff request");
    takeoff_pub -> publish(takeoff_msg);
    std::this_thread::sleep_for(std::chrono::seconds(10));

    rclcpp::Publisher<core_msgs::msg::Trajectory>::SharedPtr trajectory_pub = node -> create_publisher<core_msgs::msg::Trajectory>("/ddscore/trajectory",10);
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr attitude_sub = node -> create_publisher<geometry_msgs::msg::Twist>("/ddscore/attitude",10);
    rclcpp::Publisher<core_msgs::msg::AuxGlobalPosition>::SharedPtr aux_pub = node -> create_publisher<core_msgs::msg::AuxGlobalPosition>("/ddscore/global_position_controller",10);

    core_msgs::msg::Trajectory trajectory_msg{};
    trajectory_msg.x = 0; trajectory_msg.y = 0; trajectory_msg.z = 5; trajectory_msg.yaw = 0;

    // geometry_msgs::msg::Twist attitude_msg{};
    // attitude_msg.linear.x = 0.5;
    // attitude_msg.angular.y = 2.9;

    core_msgs::msg::AuxGlobalPosition aux_msg{};
    aux_msg.speed = 0.0;
    aux_msg.radius = 0.0;
    aux_msg.yaw = 0.0;
    aux_msg.lat = 47.5;
    aux_msg.lon = 8.54;
    aux_msg.alt = 5;

    // mode_pub -> publish(mode_msg);
    RCLCPP_INFO(node -> get_logger(), "Sending global setpoint");
    aux_pub -> publish(aux_msg);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    // while(true){
    //     try{
    //         RCLCPP_INFO(node -> get_logger(), "Sending global setpoint");
    //         trajectory_pub -> publish(trajectory_msg);
    //         attitude_sub -> publish(attitude_msg);
    //         aux_pub -> publish(aux_msg);
    //         std::this_thread::sleep_for(std::chrono::milliseconds(100));
    //     }
    //     catch(const std::exception& e){
    //         break;
    //     }
    // }
    rclcpp::shutdown();
    return 0;
}