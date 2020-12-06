#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "SdlText.h"
#include "SdlWindow.h"
#include "Event_Handler.h"
#include "MusicSoundtrack.h"
#include <map>
#include<unordered_map>
#include <utility>


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
   // SDL_Event event;
    /*
    SDL_Rect Message_rect2={165,620,100,80};
    SDL_Rect Message_rect4={30,630,70,70};
    SDL_Rect Message_rect3={0,620,1000,80};
    SDL_Surface* tmpSurface3 = IMG_Load("../Editor/Barra2.png");
    SDL_Texture* barTex = SDL_CreateTextureFromSurface(window.getRenderer(),tmpSurface3);
    SDL_Surface* tmpSurface2 = IMG_Load("../Editor/Treasure.png");
    SDL_Texture* treasureTex = SDL_CreateTextureFromSurface(window.getRenderer(),tmpSurface2);
    SDL_Surface* tmpSurface = IMG_Load("../prueba_mapa/assets/imagen1.png");
    SDL_Texture* playerTex = SDL_CreateTextureFromSurface(window.getRenderer(),tmpSurface);

    SDL_RenderCopy(window.getRenderer(), barTex, NULL, &Message_rect3);
    SDL_RenderCopy(window.getRenderer(), treasureTex, NULL, &Message_rect4); 
    SDL_RenderCopy(window.getRenderer(), playerTex, NULL, &Message_rect2); 
    window.render();
*/
    while (!quit){
        
   /*     SDL_RenderClear(window.getRenderer());
        SDL_PollEvent(&event);
        switch(event.type){
            case SDL_KEYDOWN:
                quit=true;
                break;

            case SDL_MOUSEBUTTONDOWN:
                textures.insert(std::make_pair(std::make_pair(event.button.x,event.button.y), playerTex));
                break;
        }
        SDL_RenderCopy(window.getRenderer(), barTex, NULL, &Message_rect3);
        SDL_RenderCopy(window.getRenderer(), treasureTex, NULL, &Message_rect4); 
        SDL_RenderCopy(window.getRenderer(), playerTex, NULL, &Message_rect2); 
            
        for (auto& it: textures) {
            int x=std::get<0>(it.first);
            int y=std::get<1>(it.first);
            SDL_Rect Message_rect6={x,y,100,80};
            SDL_RenderCopy(window.getRenderer(),(it.second),NULL,&Message_rect6);
        }
        window.render(); */
        quit=event_handler.handleEvents(editor);
        editor.draw();
        window.render();
    }
    //SDL_DestroyTexture(Message);
    Mix_Quit();
    SDL_Quit();
    return 0;
}