#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
/* QT */
//#include <QApplication>
//#include <QLabel>

#include "SdlSound.h"
#include "SdlText.h"
//#include "SdlTexture.h"
#include "SdlMusic.h"
#include "SdlWindow.h"
#define VOLUMEN_MAXIMO 128


int main(int argc,char* argv[]){

    std::cout << "Archivo a compilar por cmake" << std::endl;

    /* QT */
   // QApplication app(argc,argv);
    //QLabel label("Hello qt");
    //label.show();

    /* MUESTRO TEXTO CON SDL */
    bool quit = false;
    SDL_Event event;

    SdlWindow window(640,480);

    SdlText texto(window.getRenderer(),255,255,255);
    texto.Load_Text("../OpenSans-Bold.ttf","Wolfenstein",24);

    SDL_Texture* Message = SDL_CreateTextureFromSurface(window.getRenderer(), texto.getSurface()); 
    SDL_Rect Message_rect={0,0,500,500};
    SDL_RenderCopy(window.getRenderer(), Message, NULL, &Message_rect); 
    //SdlTexture texture(texto.getSurface(),window);
    //texture.render(0,0,500,500,Message_rect,Message);

    while (!quit){
        SDL_WaitEvent(&event);
        switch (event.key.keysym.sym){    
            case SDLK_ESCAPE:
            quit = true;
            break;
        }
        //texture.render(0,0,500,500,Message_rect,Message);
        //window.render();
        SDL_RenderCopy(window.getRenderer(), Message, NULL, &Message_rect);
        window.render();
    }
    SDL_DestroyTexture(Message);



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