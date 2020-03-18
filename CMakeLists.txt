cmake_minimum_required(VERSION 3.5)
project(aoa_ros)

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
endif()


find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
list(APPEND CMAKE_PREFIX_PATH "/opt/ros/kinetic")
find_package(serial REQUIRED)

include_directories(include "/opt/ros/kinetic/include")

add_executable(aoa_ros src/aoa_ros.cpp)
ament_target_dependencies(aoa_ros rclcpp std_msgs serial)
install(TARGETS
    aoa_ros
    DESTINATION lib/${PROJECT_NAME}
)

ament_package()
