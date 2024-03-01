cmake_minimum_required(VERSION 3.8)
project({{ project_name }})

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

{% for package in packages %}
find_package({{ package.name }} {{ package.type }})
{% endfor %}

if(BUILD_TESTING)
    find_package(ament_cmake_cppcheck REQUIRED)
    find_package(ament_cmake_clang_format REQUIRED)
    ament_cppcheck(src/ include/ tests/)
    ament_clang_format(src/ include/ tests/ --config ${CMAKE_CURRENT_SOURCE_DIR}/.clang-format)
endif()

add_executable({{ executables[0]["name"] }} src/remapping.cpp)
ament_target_dependencies({{ executables[0]["name"] }} {{ executables[0]["packages"] }})

add_executable({{ executables[1]["name"] }} src/main.cpp)
ament_target_dependencies({{ executables[1]["name"] }} {{ executables[1]["packages"] }})

install(TARGETS {{ executables[0]["name"] }} {{ executables[1]["name"] }} DESTINATION lib/${PROJECT_NAME})

ament_package()
