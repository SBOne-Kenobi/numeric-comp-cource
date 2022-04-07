cmake_minimum_required(VERSION 3.20)
project(integration)

set(CMAKE_CXX_STANDARD 17)

add_executable(integration main.cpp src/newton_cotes.hpp src/legendre_gauss.hpp src/abscissa.hpp src/weights.hpp)