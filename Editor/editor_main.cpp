#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "SdlClasses/SdlText.h"
#include "SdlClasses/SdlWindow.h"
#include "Event_Handler.h"
#include "MusicSoundtrack.h"
#include "YamlParser.h"
#include <fstream>  
#include <stdexcept>
#include "TextBox.h"


int main(int argc,char* argv[]){

    YAML::Node config = YAML::LoadFile("../Yaml_configs/editor_config.yaml");
    int width = config["width"].as<int>();
    int heigth =config["heigth"].as<int>();





    int error=SDL_Init(SDL_INIT_VIDEO);
    if(error!=0){
        throw std::invalid_argument("Error  en la inicializacion de sdl \n");
    }
    
    SdlWindow window(width,heigth);
    SdlText texto(window.getRenderer(),255,255,255);
    texto.Load_Text("../OpenSans-Bold.ttf","Editor",12);
    SDL_Texture* Message = SDL_CreateTextureFromSurface(window.getRenderer(), texto.getSurface()); 
    SDL_Rect Message_rect={80,300,145,80};
    SDL_RenderCopy(window.getRenderer(), Message, NULL, &Message_rect); 
    window.render();


    bool quit = false;

    SDL_Event event;

    TextBox username;
    username.box_content = "";
    
    /*
    Editor editor(window);
    Event_Handler event_handler;
    Main_Window mainwindow(window);
    mainwindow.render_window();
    window.render();
*/

    while (!quit){
        SDL_RenderClear(window.getRenderer());
        SDL_RenderCopy(window.getRenderer(), Message, NULL, &Message_rect); 
        window.render();


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
                    username.box_content += event.text.text;
                    std::cout << username.box_content << std::endl;
                    break;

        }
    }
        //quit=event_handler.handleEvents(editor);
        //editor.render();
        //window.render();
    }

    SDL_Quit();
    return 0;
}