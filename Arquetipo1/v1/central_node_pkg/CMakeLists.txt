cmake_minimum_required(VERSION 3.8)

project(central_node_pkg)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()


find_package(ament_cmake REQUIRED)

find_package(rclcpp REQUIRED)

find_package(std_msgs REQUIRED)


if (FALSE)
	if(BUILD_TESTING)
	
	find_package(ament_lint_auto REQUIRED)
	
	find_package(ament_cmake_cppcheck REQUIRED)
	
	find_package(ament_cmake_clang_format REQUIRED)
	

	set(ament_cmake_copyright_FOUND TRUE)
	set(ament_cmake_cpplint_FOUND TRUE)

	
	ament_lint_auto_find_test_dependencies()
	
	ament_cppcheck(src/ include/ tests/)
	
	ament_clang_format(src/ include/ tests/ --config ${CMAKE_CURRENT_SOURCE_DIR}/.clang-format)
	
	endif()
endif()

add_executable(central_node src/central_node.cpp src/trigger.cpp)
ament_target_dependencies(central_node rclcpp std_msgs)

install(TARGETS central_node DESTINATION lib/${PROJECT_NAME})

ament_package()