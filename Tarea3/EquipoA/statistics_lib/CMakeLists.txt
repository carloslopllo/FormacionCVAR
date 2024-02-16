cmake_minimum_required(VERSION 3.8)
project(statistics_lib)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
	add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)

include_directories(include)

add_library(statistics_lib src/movingAverage.cpp)

ament_export_targets(statistics_lib HAS_LIBRARY_TARGET)

install(
	DIRECTORY include/statistics_lib
	DESTINATION include
)

install(
	TARGETS statistics_lib
	EXPORT statistics_lib
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
	RUNTIME DESTINATION bin
	INCLUDES DESTINATION include
)

ament_package()
