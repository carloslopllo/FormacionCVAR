cmake_minimum_required(VERSION 3.8)

project(polygon_base)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
	add_compile_options(-Wall -Wextra -Wpedantic)
endif()


find_package(ament_cmake REQUIRED)



find_package(rclcpp REQUIRED)

find_package(pluginlib REQUIRED)


#if(BUILD_TESTING)
#  
#  find_package(ament_lint_auto REQUIRED)
#  
#  find_package(ament_cmake_cppcheck REQUIRED)
#  
#  find_package(ament_cmake_clang_format REQUIRED)
#  
#
#  set(ament_cmake_copyright_FOUND TRUE)
#  set(ament_cmake_cpplint_FOUND TRUE)
#
#  
#  ament_lint_auto_find_test_defaultencies()
#  
#  ament_cppcheck(src/ include/ tests/)
#  
#  ament_clang_format(src/ include/ tests/ --config ${CMAKE_CURRENT_SOURCE_DIR}/.clang-format)
#  
#endif()

add_executable(area_node src/area_node.cpp)

target_include_directories(area_node PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:include>
)

target_compile_features(area_node PUBLIC c_std_99 cxx_std_17)

ament_target_dependencies(
	area_node
	rclcpp
	"pluginlib"
)

install(
	DIRECTORY include/
	DESTINATION include
)

install(
	TARGETS area_node
	DESTINATION lib/${PROJECT_NAME}
)

ament_export_include_directories(
	include
)

ament_package()