cmake_minimum_required(VERSION 3.10)

project(Tarea3)

add_executable(main main.cpp)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)

configure_file(Config.h.in Config.h)

target_include_directories(main PUBLIC "${PROJECT_BINARY_DIR}")

add_subdirectory(statistics)
add_subdirectory(read)

target_link_libraries(main PUBLIC Statistics)
target_link_libraries(main PUBLIC Read)
