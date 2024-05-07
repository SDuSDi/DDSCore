// Base C++ libraries and dependencies
#include <cmath>

// ROS libraries and dependencies
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/empty.hpp"
#include "std_msgs/msg/float32.hpp"
#include "std_msgs/msg/int16.hpp"
#include "std_msgs/msg/bool.hpp"
#include "geometry_msgs/msg/twist.hpp"

// PX4 libraries and dependencies
#include "px4_msgs/srv/vehicle_command.hpp"
#include "px4_msgs/msg/vehicle_command.hpp"
#include "px4_msgs/msg/vehicle_command_ack.hpp"
#include "px4_msgs/msg/vehicle_global_position.hpp"
#include "px4_msgs/msg/offboard_control_mode.hpp"
#include "px4_msgs/msg/trajectory_setpoint.hpp"
#include "px4_msgs/msg/vehicle_attitude_setpoint.hpp"

// Own messages from core_msgs
#include "core_msgs/msg/trajectory.hpp"
#include "core_msgs/msg/aux_global_position.hpp"

std::array<float,3> global_pos;
bool enable = true;
px4_msgs::msg::VehicleGlobalPosition global_info{};

class ControlNode : public rclcpp::Node
{
public:
    ControlNode() : Node("ddscore")
    {
        // Definition of publishers
        vehicle_commander = this -> create_publisher<px4_msgs::msg::VehicleCommand>("/fmu/in/vehicle_command",10);
        offboard_controller = this -> create_publisher<px4_msgs::msg::OffboardControlMode>("/fmu/in/offboard_control_mode",10);
        trajectory_publisher = this -> create_publisher<px4_msgs::msg::TrajectorySetpoint>("/fmu/in/trajectory_setpoint",10);
        global_positioner = this -> create_publisher<px4_msgs::msg::VehicleGlobalPosition>("/fmu/in/aux_global_position",10);
        attitude_publisher = this -> create_publisher<px4_msgs::msg::VehicleAttitudeSetpoint>("/fmu/in/vehicle_attitude_setpoint",10);

        // Definition of quality of service for all subscribers
        rmw_qos_profile_t qos_profile = rmw_qos_profile_sensor_data;
        auto qos = rclcpp::QoS(rclcpp::QoSInitialization(qos_profile.history, 5), qos_profile);

        // Definition of service clients
        command_cl = this -> create_client<px4_msgs::srv::VehicleCommand>("/fmu/vehicle_command");

        // Definition of subscribers
        global_position_check = this -> create_subscription<px4_msgs::msg::VehicleGlobalPosition>("/fmu/out/vehicle_global_position",qos,
                                std::bind(&ControlNode::global_pos_cb, this, std::placeholders::_1));
        takeoff_srv =           this -> create_subscription<std_msgs::msg::Float32>("/ddscore/takeoff",qos, 
                                std::bind(&ControlNode::set_takeoff, this, std::placeholders::_1));
        land_srv =              this -> create_subscription<std_msgs::msg::Empty>("/ddscore/land",qos,
                                std::bind(&ControlNode::set_land, this, std::placeholders::_1));
        arm_sub =               this -> create_subscription<std_msgs::msg::Empty>("/ddscore/arm",qos,
                                std::bind(&ControlNode::arm, this, std::placeholders::_1));
        disarm_sub =            this -> create_subscription<std_msgs::msg::Empty>("/ddscore/disarm",qos,
                                std::bind(&ControlNode::disarm, this, std::placeholders::_1));
        mode_sub =              this -> create_subscription<std_msgs::msg::Int16>("/ddscore/mode",qos,
                                std::bind(&ControlNode::set_mode, this, std::placeholders::_1));
        offb_control_sub =      this -> create_subscription<std_msgs::msg::Bool>("/ddscore/offboard_control", qos,
                                std::bind(&ControlNode::offbctrl_sub, this, std::placeholders::_1));
        trajectory_sub =        this -> create_subscription<core_msgs::msg::Trajectory>("/ddscore/trajectory",qos,
                                std::bind(&ControlNode::set_trajectory, this, std::placeholders::_1));
        aux_global_sub =        this -> create_subscription<core_msgs::msg::AuxGlobalPosition>("/ddscore/global_position_controller",qos,
                                std::bind(&ControlNode::aux_global, this, std::placeholders::_1));
        attitude_sub =          this -> create_subscription<geometry_msgs::msg::Twist>("/ddscore/attitude",qos,
                                std::bind(&ControlNode::set_attitude, this, std::placeholders::_1));

        // Definition of loop timer function
        auto publish_offboard_control = [this]() -> void {
                px4_msgs::msg::OffboardControlMode msg{};
                msg.position = enable;
                msg.velocity = !enable;
                msg.acceleration = false;
                msg.attitude = false;
                msg.body_rate = false;
                msg.timestamp = this -> get_clock() -> now().nanoseconds() / 1000;
                offboard_controller -> publish(msg);
        };
        // Definition of the timer itself
        offboard_ctrl = this -> create_wall_timer(std::chrono::milliseconds(100), publish_offboard_control);
        RCLCPP_INFO(this -> get_logger(), "Node started with attitude control");

    }

private:

    void global_pos_cb(px4_msgs::msg::VehicleGlobalPosition::SharedPtr msg);

    void cb_srv_command(const rclcpp::Client<px4_msgs::srv::VehicleCommand>::SharedFuture future);
    void publish_srv_command(uint16_t command, float alt = 0.0);
    void publish_vehicle_command(uint16_t command, float param1 = 0.0);

    void set_takeoff(const std_msgs::msg::Float32::SharedPtr msg);
    void set_land(const std_msgs::msg::Empty::SharedPtr msg);
    void arm(const std_msgs::msg::Empty::SharedPtr msg);
    void disarm(const std_msgs::msg::Empty::SharedPtr msg);
    void set_mode(const std_msgs::msg::Int16::SharedPtr msg);
    void offbctrl_sub(const std_msgs::msg::Bool::SharedPtr msg);
    void set_trajectory(const core_msgs::msg::Trajectory::SharedPtr msg);
    void aux_global(const core_msgs::msg::AuxGlobalPosition::SharedPtr msg);
    void set_attitude(const geometry_msgs::msg::Twist::SharedPtr msg);

    void euler2quaternion(float roll, float pitch, float yaw, float *q);

    rclcpp::Publisher<px4_msgs::msg::VehicleCommand>::SharedPtr vehicle_commander;
    rclcpp::Publisher<px4_msgs::msg::OffboardControlMode>::SharedPtr offboard_controller;
    rclcpp::Publisher<px4_msgs::msg::TrajectorySetpoint>::SharedPtr trajectory_publisher;
    rclcpp::Publisher<px4_msgs::msg::VehicleGlobalPosition>::SharedPtr global_positioner;
    rclcpp::Publisher<px4_msgs::msg::VehicleAttitudeSetpoint>::SharedPtr attitude_publisher;

    rclcpp::Client<px4_msgs::srv::VehicleCommand>::SharedPtr command_cl;

    rclcpp::Subscription<px4_msgs::msg::VehicleGlobalPosition>::SharedPtr global_position_check;

    rclcpp::Subscription<std_msgs::msg::Float32>::SharedPtr takeoff_srv;
    rclcpp::Subscription<std_msgs::msg::Empty>::SharedPtr land_srv;
    rclcpp::Subscription<std_msgs::msg::Empty>::SharedPtr arm_sub;
    rclcpp::Subscription<std_msgs::msg::Empty>::SharedPtr disarm_sub;
    rclcpp::Subscription<std_msgs::msg::Int16>::SharedPtr mode_sub;
    rclcpp::Subscription<std_msgs::msg::Bool>::SharedPtr offb_control_sub;
    rclcpp::Subscription<core_msgs::msg::Trajectory>::SharedPtr trajectory_sub;
    rclcpp::Subscription<core_msgs::msg::AuxGlobalPosition>::SharedPtr aux_global_sub;
    rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr attitude_sub;

    rclcpp::TimerBase::SharedPtr offboard_ctrl;

};

void ControlNode::global_pos_cb(const px4_msgs::msg::VehicleGlobalPosition::SharedPtr msg) {
    global_pos[1] = msg -> lat; global_pos[2] = msg -> lon; global_pos[3] = msg -> alt;
    global_info = *msg;
}

void ControlNode::cb_srv_command(const rclcpp::Client<px4_msgs::srv::VehicleCommand>::SharedFuture future) {
    auto status = future.wait_for(std::chrono::seconds(1));
    if (status == std::future_status::ready) {
        RCLCPP_INFO(this -> get_logger(), 
        "\n\nCommand sent: %d\nResult: %d\nTarget System: %d\nTarget Component: %d\nExternal source: %d\n", 
        future.get() -> reply.command, 
        future.get() -> reply.result, 
        future.get() -> reply.target_system, 
        future.get() -> reply.target_component,
        future.get() -> reply.from_external
        );
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

void ControlNode::publish_vehicle_command(uint16_t command, float param1){
	px4_msgs::msg::VehicleCommand msg{};
	msg.param1 = param1;
	msg.command = command;
	msg.target_system = 1;
	msg.target_component = 1;
	msg.source_system = 1;
	msg.source_component = 1;
	msg.from_external = true;
	msg.timestamp = this -> get_clock() -> now().nanoseconds() / 1000;
	vehicle_commander -> publish(msg);  
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

void ControlNode::arm(const std_msgs::msg::Empty::SharedPtr msg) {
    (void) msg; //Shuts the compiler up about the empty message not being used
    RCLCPP_INFO(this -> get_logger(), "Vehicle is getting armed!");
    publish_vehicle_command(px4_msgs::msg::VehicleCommand::VEHICLE_CMD_COMPONENT_ARM_DISARM,1);
}

void ControlNode::disarm(const std_msgs::msg::Empty::SharedPtr msg) {
    (void) msg; //Shuts the compiler up about the empty message not being used
    RCLCPP_INFO(this -> get_logger(), "Vehicle is getting disarmed!");
    publish_vehicle_command(px4_msgs::msg::VehicleCommand::VEHICLE_CMD_COMPONENT_ARM_DISARM,0);
}

void ControlNode::set_mode(const std_msgs::msg::Int16::SharedPtr msg) {
    RCLCPP_INFO(this -> get_logger(), "Setting mode to: " + msg -> data);
    publish_vehicle_command(px4_msgs::msg::VehicleCommand::VEHICLE_CMD_DO_SET_MODE, msg -> data);
}

void ControlNode::offbctrl_sub(const std_msgs::msg::Bool::SharedPtr msg) {
    RCLCPP_INFO(this -> get_logger(), "Setting offboard position control to: " + msg -> data);
    enable = msg -> data;
}

void ControlNode::set_trajectory(const core_msgs::msg::Trajectory::SharedPtr msg) {
    px4_msgs::msg::TrajectorySetpoint tmp{};
    if(enable){
        tmp.position = {msg -> x, msg -> y, -(msg -> z)};
        tmp.yaw = msg -> yaw; // [-PI,PI]
        tmp.timestamp = this -> get_clock() -> now().nanoseconds() / 1000;
    }else{
        tmp.velocity = {msg -> x, msg -> y, -(msg -> z)};
        tmp.yaw = msg -> yaw; // [-PI,PI]
        tmp.timestamp = this -> get_clock() -> now().nanoseconds() / 1000;
    }
    trajectory_publisher -> publish(tmp);
}

void ControlNode::aux_global(const core_msgs::msg::AuxGlobalPosition::SharedPtr msg) {
    (void) msg;
    px4_msgs::msg::VehicleGlobalPosition tmp{};
    //TODO: Finish global control with Jose
    tmp.timestamp = this -> get_clock() -> now().nanoseconds() / 1000;
    tmp.timestamp_sample = tmp.timestamp;
    global_positioner -> publish(tmp);
}

void ControlNode::set_attitude(const geometry_msgs::msg::Twist::SharedPtr msg){
    RCLCPP_INFO(this -> get_logger(), "Doing shady shit");
    float mod = sqrt(pow(msg -> linear.x,2) + pow(msg -> linear.y,2) + pow(msg -> linear.z,2));
    float q[4];
    euler2quaternion(msg -> angular.x, msg -> angular.y, msg -> angular.z, q);
    px4_msgs::msg::VehicleAttitudeSetpoint tmp{};
    tmp.q_d = {q[0],q[1],q[2],q[3]};
    tmp.thrust_body = {0,0,-mod};
    // msg.yaw_sp_move_rate = 0.0;  //HARDCODED: YAWRATE SET TO 0 RAD/S
    tmp.timestamp = this -> get_clock() -> now().nanoseconds() / 1000;
    attitude_publisher -> publish(tmp);
}

void ControlNode::euler2quaternion(float roll, float pitch, float yaw, float *q){

    // std::array<float,3> radians = {roll * (float)M_PI / 180, pitch * (float)M_PI / 180, yaw * (float)M_PI / 180};

    float cosYaw   = cos(yaw/2.0);
    float sinYaw   = sin(yaw/2.0);
    float cosPitch = cos(pitch/2.0);
    float sinPitch = sin(pitch/2.0);
    float cosRoll  = cos(roll/2.0);
    float sinRoll  = sin(roll/2.0);

    q[0] = cosRoll * cosPitch * cosYaw + sinRoll * sinPitch * sinYaw;
    q[1] = sinRoll * cosPitch * cosYaw - cosRoll * sinPitch * sinYaw;
    q[2] = cosRoll * sinPitch * cosYaw + sinRoll * cosPitch * sinYaw;
    q[3] = cosRoll * cosPitch * sinYaw - sinRoll * sinPitch * cosYaw;
}

int main(int argc, char **argv){

    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<ControlNode>());
    rclcpp::shutdown();

    return 0;

}