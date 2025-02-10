cmake_minimum_required(VERSION 3.29)
project(skiplistv2)

set(CMAKE_CXX_STANDARD 20)
if(${CMAKE_BUILD_TYPE} STREQUAL "Release")
    set(CMAKE_CXX_FLAGS -O3)
endif()

add_executable(skiplistv2 main.cpp)
