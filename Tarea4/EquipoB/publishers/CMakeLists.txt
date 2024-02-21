cmake_minimum_required(VERSION 3.8)
project(cpp_pubsub)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
	add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

add_executable(data1 src/publisher_member_function_1.cpp)
ament_target_dependencies(data1 rclcpp std_msgs)

add_executable(data2 src/publisher_member_function_2.cpp)
ament_target_dependencies(data2 rclcpp std_msgs)

add_executable(main src/main.cpp)
ament_target_dependencies(main rclcpp std_msgs)

install(TARGETS data1 data2 main DESTINATION lib/${PROJECT_NAME})
ament_package()
