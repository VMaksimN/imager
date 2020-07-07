cmake_minimum_required(VERSION 3.1)

project(imager)

include_directories(include)
set(CMAKE_CXX_FLAGS "-g3")
add_executable(imager src/code.cpp src/image.cpp)
 
