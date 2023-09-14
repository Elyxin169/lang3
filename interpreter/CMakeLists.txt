cmake_minimum_required(VERSION 3.0)
project(lang)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Wall")

add_executable(lang main.cc)
set_target_properties(lang PROPERTIES COMPILE_FLAGS "${CMAKE_CXX_FLAGS}")
