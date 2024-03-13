cmake_minimum_required(VERSION 3.8)

project(filter)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
	add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(pluginlib REQUIRED)

add_executable(main src/main.cpp)

target_include_directories(main PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:include>
)

target_compile_features(main PUBLIC c_std_99 cxx_std_17)

ament_target_dependencies(
	main
	"pluginlib"
)

install(
	DIRECTORY include/
	DESTINATION include
)

install(
	TARGETS main
	DESTINATION lib/${PROJECT_NAME}
)

if(BUILD_TESTING)
	find_package(ament_lint_auto REQUIRED)
	set(ament_cmake_copyright_FOUND TRUE)
	set(ament_cmake_cpplint_FOUND TRUE)
	ament_lint_auto_find_test_dependencies()
endif()

ament_export_include_directories(
	include
)

ament_package()
