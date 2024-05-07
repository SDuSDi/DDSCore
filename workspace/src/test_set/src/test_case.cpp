// Libraries and dependencies
#include "rclcpp/rclcpp.hpp"

// Message libraries
#include "std_msgs/msg/int16.hpp"
#include "std_msgs/msg/empty.hpp"
#include "std_msgs/msg/float32.hpp"

int main(int argc, char **argv){

    rclcpp::init(argc, argv);
    std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("test_case");
    RCLCPP_INFO(node -> get_logger(), "Start of test case");

    rclcpp::Publisher<std_msgs::msg::Int16>::SharedPtr mode_pub = node -> create_publisher<std_msgs::msg::Int16>("/ddscore/mode",10);
    std_msgs::msg::Int16 mode_msg{};
    mode_msg.data = 1;
    RCLCPP_INFO(node -> get_logger(), "Sending request to change mode to: "+mode_msg.data);
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

    // rclcpp::Publisher<

    // while(true){
    //     try{

    //         rclcpp::spin(node);
    //     }
    //     catch(const std::exception& e){
    //         RCLCPP_INFO(node -> get_logger(), "Exception: %s", e.what());
    //         rclcpp::shutdown();
    //     }

    // }

    rclcpp::shutdown();
    return 0;
}