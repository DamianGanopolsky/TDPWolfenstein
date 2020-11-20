cmake_minimum_required(VERSION 3.19.0)

project(cmake-demo)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")

add_executable(cliente prueba_cmake_cliente.cpp)

add_executable(servidor prueba_servidor.cpp)
