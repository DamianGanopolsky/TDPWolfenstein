cmake_minimum_required(VERSION 3.19.0)

project(Wolfenstein)

find_package(Qt5Widgets)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")

add_executable(cliente prueba_cmake_cliente.cpp SdlSound.cpp SdlMusic.cpp SdlWindow.cpp SdlText.cpp)

add_executable(servidor prueba_servidor.cpp)

add_executable(client-model client-model/main.cpp client-model/Main_window.cpp)

add_executable(ray-test ray_casting/ray_test.cpp ray_casting/Ray_shotter.cpp ray_casting/Ray.cpp)

target_link_libraries(cliente SDL2 SDL2_mixer SDL2_ttf Qt5::Widgets)

target_link_libraries(client-model Qt5::Widgets)
