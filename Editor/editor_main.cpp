#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include "SdlClasses/SdlWindow.h"
#include "Event_Handler.h"
#include "MusicSoundtrack.h"
#include "Main_Window.h"


int main(int argc,char* argv[]){

    bool quit = false;
    Event_Handler event_handler;
    SdlWindow window(1024,768);
    Editor editor(window);
    EditorSoundtrack musicsoundtrack;
    musicsoundtrack.play_editor();
    Main_Window mainwindow(window);
    mainwindow.render_window();
    window.render();
/*
    SDL_Rect Message_rect={165,608,32,32};
    SDL_Surface* tmpSurface = IMG_Load("../Editor/Tile2.jpg");
    SDL_Texture* playerTex = SDL_CreateTextureFromSurface(window.getRenderer(),tmpSurface);
    SDL_RenderCopy(window.getRenderer(), playerTex, NULL, &Message_rect); 
    SDL_Surface* tmpSurface3 = IMG_Load("../Editor/Barra2.png");
    SDL_Surface* tmpSurface2 = IMG_Load("../Editor/Treasure.png");
    SDL_Surface* tmpSurface = IMG_Load("../prueba_mapa/assets/imagen1.png");
    SDL_Texture* barTex = SDL_CreateTextureFromSurface(window.getRenderer(),tmpSurface3);
    SDL_Texture* treasureTex = SDL_CreateTextureFromSurface(window.getRenderer(),tmpSurface2);
    SDL_Texture* playerTex = SDL_CreateTextureFromSurface(window.getRenderer(),tmpSurface);*/

    //SDL_Event event;

    while (!quit){
        SDL_RenderClear(window.getRenderer());
        quit=event_handler.handleEvents(editor);
        editor.render();
        /*
        SDL_Rect Message_rect2={165,608,100,80};
        SDL_Rect Message_rect4={30,630,70,70};
        SDL_Rect Message_rect3={0,608,1024,92};
        
        int error=SDL_RenderCopy(window.getRenderer(), barTex, NULL, &Message_rect3);
        if(error!=0){
            std::cout << "error" << SDL_GetError() << std::endl;
        }
        SDL_RenderCopy(window.getRenderer(), treasureTex, NULL, &Message_rect4); 
        SDL_RenderCopy(window.getRenderer(), playerTex, NULL, &Message_rect2); */
        window.render();
        //SDL_Delay(500);

       // SDL_PollEvent(&event);
    /*
        switch (event.type){ 
            case SDL_KEYDOWN:
                case SDLK_ESCAPE:
                    quit=true;
                    break;
                default:
                    break;
        }  */
        /*
        SDL_RenderClear(window.getRenderer());
        SDL_RenderCopy(window.getRenderer(), playerTex, NULL, &Message_rect); 
        mainwindow.render_window();
        window.render();*/
    }

    SDL_Quit();
    return 0;
}