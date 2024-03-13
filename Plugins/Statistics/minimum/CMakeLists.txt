cmake_minimum_required(VERSION 3.8)

project(minimum)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
	add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(ament_cmake_ros REQUIRED)
find_package(filter REQUIRED)
find_package(pluginlib REQUIRED)
pluginlib_export_plugin_description_file(filter plugins.xml)

add_library(minimum src/minimum.cpp)
add_library(minimum::minimum ALIAS minimum)
target_compile_features(minimum PUBLIC c_std_99 cxx_std_17)
target_include_directories(minimum PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:include>
)

ament_target_dependencies(
	minimum
	"filter"
	"pluginlib"
)

target_compile_definitions(minimum PRIVATE "MINIMUM_BUILDING_LIBRARY")

install(
	DIRECTORY include/
	DESTINATION include
)

install(
	TARGETS minimum
	EXPORT export_${PROJECT_NAME}
	ARCHIVE DESTINATION lib
	LIBRARY DESTINATION lib
	RUNTIME DESTINATION bin
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

ament_export_libraries(
	minimum
)

ament_export_targets(
	export_${PROJECT_NAME}
)

ament_package()
