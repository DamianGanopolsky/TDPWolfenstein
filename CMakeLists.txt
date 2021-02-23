cmake_minimum_required(VERSION 3.16.0)

project(Wolfenstein)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")

file(GLOB_RECURSE ray_casting_src "client/*.cpp")

file(GLOB_RECURSE editor_src "Editor/*.cpp")

file(GLOB_RECURSE common_src "Common/*.cpp")

file(GLOB_RECURSE server_src "Server/*.cpp")


add_executable(editor ${editor_src} Common/exception.cpp)

target_link_libraries(editor SDL2 SDL2_ttf SDL2_image yaml-cpp)

add_executable(client ${ray_casting_src} ${common_src}) 

target_link_libraries(client SDL2 SDL2_ttf SDL2_image SDL2_mixer pthread yaml-cpp)

add_executable(server ${server_src} ${common_src} Editor/YamlParser.cpp)

target_link_libraries(server pthread yaml-cpp)


set(BINARIES_DIRPATH "usr/bin")
set(SHAREDLIBS_DIRPATH "usr/lib")


install(TARGETS editor DESTINATION ${BINARIES_DIRPATH} PERMISSIONS WORLD_READ WORLD_WRITE WORLD_EXECUTE)

install(TARGETS client DESTINATION ${BINARIES_DIRPATH} PERMISSIONS WORLD_READ WORLD_WRITE WORLD_EXECUTE)

install(TARGETS server DESTINATION ${BINARIES_DIRPATH} PERMISSIONS WORLD_READ WORLD_WRITE WORLD_EXECUTE)