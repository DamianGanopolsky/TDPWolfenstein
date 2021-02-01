#include "EditorManager.h"

EditorManager::EditorManager(){
    int error=SDL_Init(SDL_INIT_VIDEO);
    if(error!=0){
        throw std::invalid_argument("Error  en la inicializacion de sdl \n");
    }
}


void EditorManager::start(){
    
    YAML::Node config = YAML::LoadFile("../Yaml_configs/editor_config.yaml");
    int width = config["width"].as<int>();
    int heigth =config["heigth"].as<int>();
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
    //SDL_Quit();
}

EditorManager::~EditorManager(){
    SDL_Quit();
}