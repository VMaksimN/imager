cmake_minimum_required(VERSION 3.1)

project(imager)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_COMPILER g++)
set(CMAKE_C_COMPILER gcc++)

include_directories(include)
#set(CMAKE_CXX_FLAGS "-g3")
add_executable(imager src/code.cpp src/image.cpp src/colors.cpp)
 
