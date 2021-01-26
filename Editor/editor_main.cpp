#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
//#include "SdlClasses/SdlText.h"
#include "SdlClasses/SdlWindow.h"
#include "Event_Handler.h"
#include "MusicSoundtrack.h"
#include "YamlParser.h"
#include <fstream>  
#include <stdexcept>
//#include "TextBox.h"

#include <sys/types.h>
#include <dirent.h>


int main(int argc,char* argv[]){

    YAML::Node config = YAML::LoadFile("../Yaml_configs/editor_config.yaml");
    int width = config["width"].as<int>();
    int heigth =config["heigth"].as<int>();

    std::string directory_path="../Maps";
    std::vector<std::string> v;
    DIR* dirp = opendir(directory_path.c_str());
    struct dirent * dp;
    while ((dp = readdir(dirp)) != NULL) {
        v.push_back(dp->d_name);
    }
    closedir(dirp);

    for(std::vector<std::string>::iterator it = v.begin(); it != v.end(); ++it) {
        std::cout << *it << std::endl;
    }

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