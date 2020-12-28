#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include "SdlClasses/SdlWindow.h"
#include "Event_Handler.h"
#include "MusicSoundtrack.h"
#include <unistd.h>
#include "yaml-cpp/yaml.h"
#include <fstream>  
#include <stdexcept>


int main(int argc,char* argv[]){

    YAML::Node config = YAML::LoadFile("../Yaml_configs/editor_config.yaml");
    int width = config["width"].as<int>();
    int heigth =config["heigth"].as<int>();
    bool quit = false;
    int error=SDL_Init(SDL_INIT_VIDEO);
    if(error==0){
        throw std::invalid_argument("Error  en la inicializacion de sdl \n");
    }
    Event_Handler event_handler;
    SdlWindow window(width,heigth);
    Editor editor(window);
    //EditorSoundtrack musicsoundtrack;
   // musicsoundtrack.play_editor();
    Main_Window mainwindow(window);
    mainwindow.render_window();
    window.render();

    while (!quit){
        SDL_RenderClear(window.getRenderer());
        quit=event_handler.handleEvents(editor);
        editor.render();
        window.render();
    }

    SDL_Quit();
    return 0;
}