cmake_minimum_required(VERSION 3.19.0)

project(Wolfenstein)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")

add_executable(cliente prueba_cmake_cliente.cpp Prueba_sonido.cpp Music.cpp)

add_executable(servidor prueba_servidor.cpp)

target_link_libraries(cliente SDL2 SDL2_mixer)

