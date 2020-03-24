# new package 
cmake_minimum_required(VERSION 2.8.3)
project(aoa_ros)


find_package(catkin REQUIRED COMPONENTS
  roscpp
  serial
  std_msgs
  geometry_msgs
  message_generation
)

# ulimit -c unlimited
# ssh firefly@192.168.1.76
add_compile_options(-g -std=c++11)    #-g -> core dumped



add_message_files(
  FILES
  aoa_msg.msg
)
## Generate added messages and services with any dependencies listed here
generate_messages(
   DEPENDENCIES
   std_msgs
 )
catkin_package(
  CATKIN_DEPENDS
  message_runtime
  INCLUDE_DIRS include
  LIBRARIES xiaoyuan_robot
#  CATKIN_DEPENDS geometry_msgs message_generation nav_msgs nav_msgs roscpp roslib rospy sensor_msgs std_msgs tf
  #DEPENDS system_lib
)


# defind robot status massage
# command atkin_make -DCATKIN_WHITELIST_PACKAGES="new_msg"
include_directories(include ${catkin_INCLUDE_DIRS} ${PCL_INCLUDE_DIRS})
include_directories(
    include
    include/${PROJECT_NAME}
)

add_executable(aoa_ros src/aoa_ros.cpp)
target_link_libraries(aoa_ros ${catkin_LIBRARIES})

