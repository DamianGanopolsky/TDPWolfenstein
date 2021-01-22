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
    
    YAML::Node map= YAML::LoadFile("../Maps/Simple.yaml");
    //int x=map['0']["position"].as<int>();
    const YAML::Node& position = map['0'];
    for (YAML::const_iterator it = position["position"].begin(); it != position["position"].end(); ++it) {
        const YAML::Node& pos = *it;
        std::cout << pos['x'] << std::endl;
        std::cout << pos['y'] << std::endl;
    }

    const YAML::Node& position2 = map['1'];
    for (YAML::const_iterator it = position2["position"].begin(); it != position2["position"].end(); ++it) {
        const YAML::Node& pos = *it;
        std::cout << pos['x'] << std::endl;
        std::cout << pos['y'] << std::endl;
    }
    //int y=position["position"].as<int>();
    //std::cout << y << std::endl;
    //std::cout << x << std::endl;


    int error=SDL_Init(SDL_INIT_VIDEO);
    if(error!=0){
        throw std::invalid_argument("Error  en la inicializacion de sdl \n");
    }
    
    SdlWindow window(width,heigth);
    Editor editor(window);
    Event_Handler event_handler;
    bool quit = false;
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