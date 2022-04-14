cmake_minimum_required(VERSION 3.20)
project(diff)

set(CMAKE_CXX_STANDARD 17)

add_executable(diff main.cpp src/diff_euler.hpp)

target_compile_definitions(diff PUBLIC
    "RESOURCES_DIR=\"${CMAKE_CURRENT_SOURCE_DIR}/resources\""
)
