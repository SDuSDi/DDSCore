#! /bin/bash
set -e 
source microros_ws/install/setup.bash && ros2 run micro_ros_agent micro_ros_agent udp4 --port 8888 &
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/root/microros_ws/install/px4_msgs/lib/ #Arregla un problema de path de ddscore
source /opt/ros/humble/setup.bash && cd workspace && colcon build && source install/setup.bash && ros2 run core node