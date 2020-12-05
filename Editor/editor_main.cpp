#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "SdlText.h"
#include "SdlWindow.h"
#include "Event_Handler.h"


int main(int argc,char* argv[]){

    bool quit = false;
    Event_Handler event_handler;
    
    SdlWindow window(1024,760);
    Editor editor(window);

    while (!quit){
        quit=event_handler.handleEvents(editor);
        editor.draw();
        
        window.render();
    }
    //SDL_DestroyTexture(Message);
    return 0;
}