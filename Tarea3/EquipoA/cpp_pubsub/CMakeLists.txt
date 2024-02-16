cmake_minimum_required(VERSION 3.8)

project(cpp_pubsub)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
	add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(statistics_lib REQUIRED)

add_executable(talker src/publisher_member_function.cpp)
ament_target_dependencies(talker rclcpp std_msgs)

add_executable(listener src/subscriber_member_function.cpp)
ament_target_dependencies(listener statistics_lib rclcpp std_msgs)

add_executable(output src/output.cpp)
ament_target_dependencies(output rclcpp std_msgs)

install(TARGETS talker listener output DESTINATION lib/${PROJECT_NAME})

ament_package()
