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


int main(int argc,char* argv[]){

    YAML::Node config = YAML::LoadFile("../Yaml_configs/editor_config.yaml");
    int width = config["width"].as<int>();
    int heigth =config["heigth"].as<int>();

    int error=SDL_Init(SDL_INIT_VIDEO);
    if(error!=0){
        throw std::invalid_argument("Error  en la inicializacion de sdl \n");
    }
    
    SdlWindow window(width,heigth);
/*
    SdlText texto(window.getRenderer(),255,255,255);
    SDL_Rect Message_rect={80,300,145,80};
    SDL_Event event;
    TextBox username;
    username.box_content = "";
    SDL_Texture* Message;
    texto.Load_Text("../OpenSans-Bold.ttf",username.box_content,12);
    Message = SDL_CreateTextureFromSurface(window.getRenderer(), texto.getSurface());
    window.render(); */

    Editor editor(window);
    Event_Handler event_handler;
    bool quit = false;
    Main_Window mainwindow(window);
    mainwindow.render_window();
    window.render();


    while (!quit){
/*
        while(SDL_PollEvent(&event)!=0){
            switch (event.type){    
                case SDL_QUIT:
                    quit=true;
                    break;

                case SDL_KEYDOWN:

                    switch(event.key.keysym.sym){
                        case SDLK_ESCAPE:  //Salir de la pantalla
                            quit=true;
                            break;
                    }
                    break;
                case SDL_TEXTINPUT:
                    std::cout << "asd" << std::endl;
                    username.box_content += event.text.text;
                    texto.Load_Text("../OpenSans-Bold.ttf",username.box_content,12);
                    Message = SDL_CreateTextureFromSurface(window.getRenderer(), texto.getSurface()); 
                    std::cout << username.box_content << std::endl;
                    break;
        }
        SDL_RenderClear(window.getRenderer());
        SDL_RenderCopy(window.getRenderer(), Message, NULL, &Message_rect); 
        window.render();

    }*/
        SDL_RenderClear(window.getRenderer());
        quit=event_handler.handleEvents(editor);
        editor.render();
        window.render();
    }

    SDL_Quit();
    return 0;
}