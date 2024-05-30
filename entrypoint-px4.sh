#! /bin/bash
set -e
source microros_ws/install/setup.bash && ros2 run micro_ros_agent micro_ros_agent udp4 --port 8888 &
cd PX4-Autopilot && HEADLESS=1 make px4_sitl gz_x500