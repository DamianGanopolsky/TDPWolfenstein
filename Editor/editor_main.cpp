#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "SdlClasses/SdlText.h"
#include "SdlClasses/SdlWindow.h"
#include "Event_Handler.h"
#include "MusicSoundtrack.h"
#include "Main_Window.h"


int main(int argc,char* argv[]){

    bool quit = false;
    Event_Handler event_handler;
    std::map<std::pair<int,int>,SDL_Texture*> textures;
    std::pair <int,int> xy;
    SdlWindow window(1024,760);
    Editor editor(window);

    if(SDL_Init(SDL_INIT_AUDIO)==-1) {
        printf("SDL_Init: %s\n", SDL_GetError());
    }
    if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,1024)<0){
        std::cout << "eRROR:" << Mix_GetError() << std::endl;
    }
    EditorSoundtrack musicsoundtrack;
    musicsoundtrack.load_editor_soundtrack();
    musicsoundtrack.play_editor();
    Main_Window mainwindow(window);
    mainwindow.render_window();
    window.render();

    while (!quit){
        quit=event_handler.handleEvents(editor);
        editor.draw();
        window.render();
    }
    //SDL_DestroyTexture(Message);
    Mix_Quit();
    SDL_Quit();
    return 0;
}