#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include "SdlClasses/SdlWindow.h"
#include "Event_Handler.h"
#include "MusicSoundtrack.h"
#include <unistd.h>
#define WIDTH 640
#define HEIGTH 480


int main(int argc,char* argv[]){

    bool quit = false;
    Event_Handler event_handler;
    SdlWindow window(WIDTH,HEIGTH);
    Editor editor(window);
    EditorSoundtrack musicsoundtrack;
    musicsoundtrack.play_editor();
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