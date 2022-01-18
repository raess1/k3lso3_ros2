# ROS2 Packages for K3lso v2 Quadruped Robot

Tested with:

* Ubuntu 20.04 (Linux Mint 20.1) & ROS2 Foxy Fitzroy

## Packages documentation

* [k3lso_msgs](https://github.com/edgarcamilocamacho/k3lso3_ros2/tree/master/k3lso_msgs)
* [k3lso_description](https://github.com/edgarcamilocamacho/k3lso3_ros2/tree/master/k3lso_description)
* [k3lso_vectornav](https://github.com/edgarcamilocamacho/k3lso3_ros2/tree/master/k3lso_vectornav)
* [k3lso_moteus](https://github.com/edgarcamilocamacho/k3lso3_ros2/tree/master/k3lso_moteus)

## Installation


## Notes

#Vectornav

When you open a terminal, you need to do:  
source ~/startRos2.sh

Then go to the workspace and enable it:  
cd ~/ros2_ws/k3lso3_ws/  
source install/setup.bash  

And run the node:  
ros2 run k3lso_vectornav k3lso_vectornav

The files you should check are:  
~/ros2_ws/k3lso3_ws/src/k3lso3_ros2/k3lso_vectornav/src/k3lso_vectornav_node.cpp  
~/ros2_ws/k3lso3_ws/src/k3lso3_ros2/k3lso_vectornav/src/rt/rt_vectornav.cpp  

The second one has the port and rate.  

When you change something, you need to do 'colcon build' at the workspace root.  

#Start rviz enable tau


source ~/startRos2.sh

cd ~/ros2_ws/k3lso3_ws/

source install/setup.bash

ros2 run k3lso_moteus k3lso_moteus_node

terminal 2

ros2 launch k3lso_description k3lso_rviz.launch.py



