cmake_minimum_required(VERSION 3.24)
project(cpplearn LANGUAGES CXX)
find_package(benchmark REQUIRED)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(cpplearn
        src/meetings.cpp src/simple.cpp)



add_executable(simple src/simple.cpp)

add_executable(pairwise src/pairwise.cpp src/pairwise.cpp)

add_executable(bench src/benchmark.cpp)

add_executable(min src/min_element.cpp)
target_link_libraries(bench PRIVATE benchmark::benchmark)