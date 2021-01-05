#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "SdlSound.h"
#include "../Editor/SdlClasses/SdlMusic.h"
#include "../Editor/SdlClasses/SdlWindow.h"
//#include "SdlText.h"
//#include "SdlTexture.h"
//#include "SdlMusic.h"
//#include "SdlWindow.h"
#include "yaml-cpp/yaml.h"
#define VOLUMEN_MAXIMO 128


int main(int argc,char* argv[]){

    YAML::Node config = YAML::LoadFile("../Yaml_configs/editor_config.yaml");
    int width = config["width"].as<int>();
    int heigth =config["heigth"].as<int>();


    /* MUESTRO TEXTO CON SDL */
    bool quit = false;
    SDL_Event event;
    SdlWindow window(width,heigth);

    SDL_Surface* background_surf=IMG_Load("../Assets/Login/Background.jpg");
    if(!background_surf) {
    printf("IMG_Load: %s\n", IMG_GetError());
    // handle error
}
    SDL_Texture* background=SDL_CreateTextureFromSurface(window.getRenderer(),background_surf);
    //SdlText texto(window.getRenderer(),255,255,255);
    //texto.Load_Text("../OpenSans-Bold.ttf","Wolfenstein",24);

    //SDL_Texture* Message = SDL_CreateTextureFromSurface(window.getRenderer(), texto.getSurface()); 
    SDL_Rect Message_rect={0,0,width,heigth};
    SDL_RenderCopy(window.getRenderer(), background, NULL, &Message_rect); 

    while (!quit){
        SDL_WaitEvent(&event);
        switch (event.key.keysym.sym){    
            case SDLK_ESCAPE:
            quit = true;
            break;
        }
        SDL_RenderCopy(window.getRenderer(), background, NULL, &Message_rect);
        window.render();
    }
   // SDL_DestroyTexture(Message);



    /* PRUEBAS DE "CONCEPTO" DE MUSICA Y SONIDOS */

    if(SDL_Init(SDL_INIT_AUDIO)==-1) {
        printf("SDL_Init: %s\n", SDL_GetError());
    }
    if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,1024)<0){
        std::cout << "eRROR:" << Mix_GetError() << std::endl;
    }
    SdlSound sonido("../Sounds/SS_Agent_death.wav");
    sonido.play(VOLUMEN_MAXIMO);

    SdlMusic music("../Music/menu.mp3");
    music.play();

    Mix_Quit();
    SDL_Quit();

    return 0;
}