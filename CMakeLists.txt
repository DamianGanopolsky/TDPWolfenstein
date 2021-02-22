cmake_minimum_required(VERSION 3.19.0)

project(Wolfenstein)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")

file(GLOB ray_casting_dep_3 "client/SdlClasses/*.cpp")

file(GLOB ray_casting_dep "client/*.cpp")

file(GLOB ray_casting_dep_2 "client/panel_status/*.cpp")

file(GLOB ray_casting_dep_4 "client/Yaml/*.cpp")

file(GLOB ray_casting_dep_5 "client/ClientConnector/*.cpp")

file(GLOB_RECURSE common "Common/*.cpp")

file(GLOB_RECURSE server "Server/*.cpp")

add_library(common-lib SHARED ${common})


add_executable(editor Editor/editor_main.cpp Editor/SdlClasses/SdlWindow.cpp Editor/SdlClasses/SdlText.cpp Editor/Event_Handler.cpp Editor/Editor.cpp Editor/Scene.cpp Editor/Main_Window.cpp Editor/Map.cpp Editor/YamlParser.cpp Editor/InputTextView.cpp Editor/MapOptionsView.cpp Editor/MapButton.cpp Editor/EditorManager.cpp Common/exception.cpp)

add_executable(Client ${ray_casting_dep_3} ${ray_casting_dep} ${ray_casting_dep_2} ${ray_casting_dep_4} ${ray_casting_dep_5} ${common}  ) 

add_executable(servidor ${server} Editor/YamlParser.cpp)

target_link_libraries(servidor common-lib pthread yaml-cpp)

target_link_libraries(editor SDL2 SDL2_ttf SDL2_image yaml-cpp)

target_link_libraries(Client SDL2 SDL2_image pthread SDL2_mixer yaml-cpp SDL2_ttf)

