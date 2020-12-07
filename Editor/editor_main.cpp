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
    SDL_RenderCopy(window.getRenderer(), playerTex, NULL, &Message_rect); */
    SDL_Event event;

    while (!quit){
        SDL_RenderClear(window.getRenderer());
        //quit=event_handler.handleEvents(editor);
        //editor.render();
       // window.render();

        SDL_PollEvent(&event);
    
        switch (event.type){ 
            case SDL_KEYDOWN:
                quit=true;
                break;

        }  /*
        SDL_RenderClear(window.getRenderer());
        SDL_RenderCopy(window.getRenderer(), playerTex, NULL, &Message_rect); */
        mainwindow.render_window();
        window.render();
    }

    SDL_Quit();
    return 0;
}