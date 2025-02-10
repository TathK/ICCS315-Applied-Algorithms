cmake_minimum_required(VERSION 3.29)
project(b_tree_2)

set(CMAKE_CXX_STANDARD 20)

add_executable(b_tree_2 main.cpp)
include_directories(${CMAKE_SOURCE_DIR})

include(FetchContent)


FetchContent_Declare(
        google_benchmark
        GIT_REPOSITORY https://github.com/google/benchmark.git
        GIT_TAG        v1.9.1
)
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(google_benchmark)


target_include_directories(b_tree_2
        PRIVATE
        ${nanobench_SOURCE_DIR}
)

target_link_libraries(b_tree_2
        PRIVATE
        benchmark::benchmark
        benchmark::benchmark_main
)


if(${CMAKE_BUILD_TYPE} STREQUAL "Release")
    set(CMAKE_CXX_FLAGS -O3)
endif()


