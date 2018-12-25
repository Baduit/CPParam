cmake_minimum_required(VERSION 3.0)

project(test_param)

add_definitions(-std=c++1z)

set(SRCS src/main.cpp)

include_directories(test_param PRIVATE ./src)
add_executable(test_param ${SRCS})
