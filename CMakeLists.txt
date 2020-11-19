cmake_minimum_required(VERSION 3.19.0)

project(cmake-demo)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")

add_executable(ejecutable prueba_cmake.cpp)
