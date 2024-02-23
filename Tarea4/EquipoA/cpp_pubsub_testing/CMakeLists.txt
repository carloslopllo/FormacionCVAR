cmake_minimum_required(VERSION 3.8)

project(cpp_pubsub_testing)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
	add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(statistics_lib REQUIRED)

include_directories(include)

add_executable(talker src/publisher_main.cpp src/publisher.cpp src/reader.cpp)
ament_target_dependencies(talker rclcpp std_msgs)

add_executable(listener src/subscriber_main.cpp src/subscriber_member_function.cpp)
ament_target_dependencies(listener rclcpp std_msgs statistics_lib)

add_executable(output src/output_main.cpp src/output.cpp)
ament_target_dependencies(output rclcpp std_msgs)

if(BUILD_TESTING)
  find_package(ament_cmake_gtest REQUIRED)

  configure_file(test/samples/samples1.in ${CMAKE_CURRENT_BINARY_DIR}/samples1.in COPYONLY)
  configure_file(test/samples/samples1.out ${CMAKE_CURRENT_BINARY_DIR}/samples1.out COPYONLY)
  configure_file(test/samples/samples2.in ${CMAKE_CURRENT_BINARY_DIR}/samples2.in COPYONLY)
  configure_file(test/samples/samples2.out ${CMAKE_CURRENT_BINARY_DIR}/samples2.out COPYONLY)
  configure_file(test/samples/samples3.out ${CMAKE_CURRENT_BINARY_DIR}/samples3.out COPYONLY)

  ament_add_gtest(${PROJECT_NAME}_tutorial_test test/my_tests.cpp src/reader.cpp src/output.cpp src/publisher.cpp src/subscriber_member_function.cpp)
  target_compile_options(${PROJECT_NAME}_tutorial_test PRIVATE -DGTEST_VERBOSE=1)

  ament_add_gtest(${PROJECT_NAME}_tutorial_test2 test/my_tests2.cpp src/reader.cpp src/output.cpp src/publisher.cpp src/subscriber_member_function.cpp)
  target_compile_options(${PROJECT_NAME}_tutorial_test PRIVATE -DGTEST_VERBOSE=1)

  target_include_directories(${PROJECT_NAME}_tutorial_test PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
	${CMAKE_CURRENT_BINARY_DIR}
  )
  ament_target_dependencies(${PROJECT_NAME}_tutorial_test
    std_msgs rclcpp statistics_lib
  )

  target_include_directories(${PROJECT_NAME}_tutorial_test2 PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    ${CMAKE_CURRENT_BINARY_DIR}
  )
ament_target_dependencies(${PROJECT_NAME}_tutorial_test2
  std_msgs rclcpp statistics_lib
)
  #target_link_libraries(${PROJECT_NAME}_tutorial_test name_of_local_library)
endif()

install(TARGETS talker listener output DESTINATION lib/${PROJECT_NAME})

ament_package()