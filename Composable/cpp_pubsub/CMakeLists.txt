cmake_minimum_required(VERSION 3.8)

project(cpp_pubsub)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
	add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(rclcpp_components REQUIRED)

if(BUILD_TESTING)
	find_package(ament_lint_auto REQUIRED)
	set(ament_cmake_copyright_FOUND TRUE)
	set(ament_cmake_cpplint_FOUND TRUE)
	ament_lint_auto_find_test_dependencies()
endif()

add_library(talker_component SHARED src/publisher_member_function.cpp)
ament_target_dependencies(talker_component rclcpp std_msgs rclcpp_components)

rclcpp_components_register_node(
	talker_component
	PLUGIN "Composable::MinimalPublisher"
	EXECUTABLE talker
)

ament_export_targets(export_talker_component)

install(
	TARGETS talker_component
	EXPORT export_talker_component
	ARCHIVE DESTINATION lib
	LIBRARY DESTINATION lib
	RUNTIME DESTINATION bin
)

ament_package()