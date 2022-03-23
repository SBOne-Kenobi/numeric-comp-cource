cmake_minimum_required(VERSION 3.20)
project(reg_int)

set(CMAKE_CXX_STANDARD 17)

add_executable(reg_int main.cpp src/linear_int.hpp src/lagrange_int.hpp)