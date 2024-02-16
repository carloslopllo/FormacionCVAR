add_library(Statistics maximum.cpp minimum.cpp movingAverage.cpp)

target_include_directories(Statistics INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
