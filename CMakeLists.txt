cmake_minimum_required(VERSION 3.24)
project(cpplearn)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(cpplearn
        src/meetings.cpp)
#        src/meetings.h
#        src/mess.cpp
#        test/meetings_test.cpp)
