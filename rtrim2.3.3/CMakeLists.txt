cmake_minimum_required(VERSION 3.17)
project(rtrim2_3_3)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")

add_executable(rtrim2_3_3 main.cpp)