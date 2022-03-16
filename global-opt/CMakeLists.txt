cmake_minimum_required(VERSION 3.20)
project(global_opt)

set(CMAKE_CXX_STANDARD 17)

add_executable(global_opt main.cpp src/random_search.hpp src/lipo.hpp src/genetic.hpp)