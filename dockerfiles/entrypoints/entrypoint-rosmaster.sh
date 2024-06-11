#! /bin/bash
set -e
# mosquitto -p 1883 &
source /opt/ros/humble/setup.bash && cd master && colcon build && source install/setup.bash && ros2 run master node