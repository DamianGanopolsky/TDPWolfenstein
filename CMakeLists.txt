cmake_minimum_required(VERSION 3.19.0)

project(Wolfenstein)

find_package(Qt5Widgets)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")

add_executable(cliente prueba_cmake_cliente.cpp SdlSound.cpp SdlMusic.cpp SdlWindow.cpp SdlText.cpp)

add_executable(editor Editor/editor_main.cpp Editor/SdlWindow.cpp Editor/SdlText.cpp Editor/Event_Handler.cpp)

add_executable(servidor prueba_servidor.cpp)

add_executable(client-model client-model/main.cpp client-model/Main_window.cpp)

add_executable(ray-test ray_casting/ray_test.cpp ray_casting/Ray_shotter.cpp ray_casting/Ray.cpp)

add_executable(panel ray_casting/main.cpp ray_casting/Player.cpp ray_casting/Map_2d.cpp ray_casting/Panel_window.cpp ray_casting/Ray_shotter.cpp ray_casting/Ray.cpp ray_casting/Event_handler.cpp)

target_link_libraries(cliente SDL2 SDL2_mixer SDL2_ttf)

target_link_libraries(editor SDL2 SDL2_mixer SDL2_ttf)

target_link_libraries(client-model Qt5::Widgets)

target_link_libraries(panel SDL2)
