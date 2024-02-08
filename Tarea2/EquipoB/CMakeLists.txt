cmake_minimum_required(VERSION 3.10)

project(Tarea2 VERSION 1.0)

add_executable(Tarea2 mainfiltro.cpp mediamovil.cpp maximo.cpp)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(VERSION_MAJOR 1)
set(VERSION_MINOR 1)

configure_file(Config.h.in Config.h)
target_include_directories(Tarea2 PUBLIC "${PROJECT_BINARY_DIR}")
