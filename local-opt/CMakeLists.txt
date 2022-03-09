cmake_minimum_required(VERSION 3.20)
project(local_opt)

set(CMAKE_CXX_STANDARD 17)

add_executable(local_opt main.cpp src/bisection.hpp src/utils.hpp src/newton.hpp)