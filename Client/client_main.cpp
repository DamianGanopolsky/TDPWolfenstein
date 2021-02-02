#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "SdlSound.h"
//#include "../Editor/SdlClasses/SdlMusic.h"
#include "../Editor/SdlClasses/SdlWindow.h"
#include "yaml-cpp/yaml.h"
#define VOLUMEN_MAXIMO 128


int main(int argc,char* argv[]){

    if(SDL_Init(SDL_INIT_AUDIO)==-1) {
        printf("SDL_Init: %s\n", SDL_GetError());
    }
   /* if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,1024)<0){
        std::cout << "eRROR:" << Mix_GetError() << std::endl;
    }*/
    YAML::Node config = YAML::LoadFile("../Yaml_configs/editor_config.yaml");
    int width = config["width"].as<int>();
    int heigth =config["heigth"].as<int>();
    bool quit = false;
    SDL_Event event;
    SdlWindow window(width,heigth);
    SDL_Surface* background_surf=IMG_Load("../Assets/Login/mainscreen.jpg");
    SDL_Texture* background=SDL_CreateTextureFromSurface(window.getRenderer(),background_surf);
    SDL_Surface* not_clicked_bar_surf=IMG_Load("../Assets/Login/Unpressed_bar.png");
    SDL_Texture* bar=SDL_CreateTextureFromSurface(window.getRenderer(),not_clicked_bar_surf);
    SDL_Surface* connect_surf=IMG_Load("../Assets/Login/Connect.png");
    SDL_Texture* connect=SDL_CreateTextureFromSurface(window.getRenderer(),connect_surf);
    SDL_Rect Message_rect={0,0,width,heigth};
    SDL_Rect Bar_Rect={374,405,180,40};
    SDL_Rect Connect_Rect={455,550,100,100};
    SDL_RenderCopy(window.getRenderer(), background, NULL, &Message_rect); 
    SDL_RenderCopy(window.getRenderer(), bar, NULL, &Bar_Rect); 
    SDL_RenderCopy(window.getRenderer(), connect, NULL, &Connect_Rect); 

    //SdlMusic music("../Music/menu.mp3");
    //music.play();

    while(quit!=true){
        while(SDL_PollEvent(&event)!=0){
            switch (event.type){   

                case SDL_KEYDOWN:

                    switch(event.key.keysym.sym){
                        case SDLK_ESCAPE:  //Salir de la pantalla
                            quit=true;
                            break;
                    }
                    break; 
                case SDL_QUIT:
                    quit = true;
                    break;

                case SDL_MOUSEMOTION:   
                    //std::cout << "En x:" << event.button.x << "En y:" << event.button.y << std::endl;
                    break;
            }
            SDL_RenderCopy(window.getRenderer(), background, NULL, &Message_rect);
            SDL_RenderCopy(window.getRenderer(), bar, NULL, &Bar_Rect); 
            SDL_RenderCopy(window.getRenderer(), connect, NULL, &Connect_Rect); 
            window.render();
        }
    }
   // std::cout << "FInalizo" << std::endl;

   // Mix_Quit();
    SDL_Quit();
    return 0;
}