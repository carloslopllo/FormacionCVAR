cmake_minimum_required(VERSION 3.8)

project(movingAverage)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
	add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(ament_cmake_ros REQUIRED)
find_package(filter REQUIRED)
find_package(pluginlib REQUIRED)
pluginlib_export_plugin_description_file(filter plugins.xml)

add_library(movingAverage src/movingAverage.cpp)
add_library(movingAverage::movingAverage ALIAS movingAverage)
target_compile_features(movingAverage PUBLIC c_std_99 cxx_std_17)
target_include_directories(movingAverage PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:include>
)

ament_target_dependencies(
	movingAverage
	"filter"
	"pluginlib"
)

target_compile_definitions(movingAverage PRIVATE "MOVINGAVERAGE_BUILDING_LIBRARY")

install(
	DIRECTORY include/
	DESTINATION include
)

install(
	TARGETS movingAverage
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
	movingAverage
)

ament_export_targets(
	export_${PROJECT_NAME}
)

ament_package()
