cmake_minimum_required(VERSION 3.20)
project(irreg_int)

set(CMAKE_CXX_STANDARD 17)

add_executable(irreg_int main.cpp src/barycentric_int.hpp src/rb_int.hpp src/point.hpp)

target_compile_definitions(irreg_int PUBLIC
    "RESOURCES_DIR=\"${CMAKE_CURRENT_SOURCE_DIR}/resources\""
)
