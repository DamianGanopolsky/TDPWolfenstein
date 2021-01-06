cmake_minimum_required(VERSION 3.19.0)

project(Wolfenstein)

find_package(Qt5Widgets)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")

file(GLOB ray_casting_dep "ray_casting/*.cpp")

add_executable(cliente Client/client_main.cpp Client/SdlSound.cpp Client/SdlMusic.cpp ../Editor/SdlClasses/SdlWindow.cpp)

add_executable(editor Editor/editor_main.cpp Editor/SdlClasses/SdlWindow.cpp Editor/SdlClasses/SdlText.cpp Editor/Event_Handler.cpp Editor/Editor.cpp Editor/Scene.cpp Editor/SdlClasses/SdlMusic.cpp Editor/MusicSoundtrack.cpp Editor/Main_Window.cpp Editor/Map.cpp)

add_executable(servidor prueba_servidor.cpp)

add_executable(client-model client-model/main.cpp client-model/Main_window.cpp)

add_executable(panel ${ray_casting_dep})

target_link_libraries(cliente SDL2 SDL2_mixer SDL2_ttf SDL2_image yaml-cpp)

target_link_libraries(editor SDL2 SDL2_mixer SDL2_ttf SDL2_image yaml-cpp)

target_link_libraries(client-model Qt5::Widgets)

target_link_libraries(panel SDL2 SDL2_image pthread)
