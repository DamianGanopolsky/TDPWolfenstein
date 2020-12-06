#include "Scene.h"

Scene::Scene(SdlWindow& Window):window(Window){
    SDL_Surface* tre_surface=IMG_Load("../Editor/Treasure.png");
    treasure=SDL_CreateTextureFromSurface(window.getRenderer(),tre_surface);
    SDL_Surface* player_surface = IMG_Load("../prueba_mapa/assets/imagen1.png");
    player=SDL_CreateTextureFromSurface(window.getRenderer(),player_surface);
    SDL_Surface* bar_surface=IMG_Load("../Editor/Barra2.png");
    bar=SDL_CreateTextureFromSurface(window.getRenderer(),bar_surface);
}

void Scene::set(){
    SDL_Rect Message_rect={165,620,100,80};
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
    SDL_RenderCopy(window.getRenderer(), playerTex, NULL, &Message_rect); 
}

void Scene::draw(position& initial_pos,position& final_pos){
    int block_frame=int(initial_pos.x)/145;
    switch(block_frame){
        case 0:
            textures.insert(std::make_pair(std::make_pair(final_pos.x,final_pos.y), treasure));
            break;
        case 1:
            textures.insert(std::make_pair(std::make_pair(final_pos.x,final_pos.y), player));
            break;
        default:
            break;
    }
}

void Scene::render(){
    SDL_Rect Message_rect={165,620,100,80};
    SDL_Rect Message_rect4={30,630,70,70};
    SDL_Rect Message_rect3={0,620,1000,80};
    SDL_RenderCopy(window.getRenderer(), bar, NULL, &Message_rect3);
    SDL_RenderCopy(window.getRenderer(), treasure, NULL, &Message_rect4); 
    SDL_RenderCopy(window.getRenderer(), player, NULL, &Message_rect); 
    for (auto& it: textures) {
        int x=std::get<0>(it.first);
        int y=std::get<1>(it.first);
        SDL_Rect Message_rect6={x,y,40,40};
        SDL_RenderCopy(window.getRenderer(),(it.second),NULL,&Message_rect6);
    }

}

void Scene::show(){
}

Scene::~Scene(){
    
}