cmake_minimum_required(VERSION 3.10)
project(compiler)

set(CMAKE_CXX_STANDARD 11)

add_executable(compiler main.cc)

target_include_directories(compiler PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
