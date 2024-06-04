// ROS libraries and dependencies
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/empty.hpp"
#include "std_msgs/msg/float32.hpp"
#include "std_msgs/msg/int16.hpp"
#include "std_msgs/msg/bool.hpp"

// Own messages from core_msgs
#include "core_msgs/msg/aux_global_position.hpp"

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
    }
private:

    rclcpp::Publisher<std_msgs::msg::Int16>::SharedPtr mode_pub;
    rclcpp::Publisher<std_msgs::msg::Empty>::SharedPtr arm_pub;
    rclcpp::Publisher<std_msgs::msg::Empty>::SharedPtr disarm_pub;
    rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr takeoff_pub;
    rclcpp::Publisher<std_msgs::msg::Empty>::SharedPtr land_pub;

};

int main(int argc, char **argv){

    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<LinkNode>());
    rclcpp::shutdown();

    return 0;
}