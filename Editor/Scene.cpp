#include "Scene.h"

Scene::Scene(SdlWindow& Window):window(Window){
    SDL_Surface* tre_surface=IMG_Load("../Editor/Treasure.png");
    treasure=SDL_CreateTextureFromSurface(window.getRenderer(),tre_surface);
    SDL_Surface* player_surface = IMG_Load("../prueba_mapa/assets/imagen1.png");
    player=SDL_CreateTextureFromSurface(window.getRenderer(),player_surface);
    SDL_Surface* bar_surface=IMG_Load("../Editor/Barra2.png");
    bar=SDL_CreateTextureFromSurface(window.getRenderer(),bar_surface);
    SDL_Surface* floor_tile_surf=IMG_Load("../Editor/Barra2.png");
    floor_tile=SDL_CreateTextureFromSurface(window.getRenderer(),floor_tile_surf);
}

void Scene::draw_initial_map(int level[][19]){
    for(int i=0;i<32;i++){
        for(int j=0;j<19;j++){
            switch(level[i][j]){
                case 0:
                    tiles.insert(std::make_pair(std::make_pair(i*32,j*32), floor_tile));
                    break;
                case 1:
                    tiles.insert(std::make_pair(std::make_pair(i*32,j*32), floor_tile));
                    textures.insert(std::make_pair(std::make_pair(i*32,j*32), treasure));
                    break;
                case 2:
                    tiles.insert(std::make_pair(std::make_pair(i*32,j*32), floor_tile));
                    textures.insert(std::make_pair(std::make_pair(i*32,j*32), player));
                    break;
                default:
                    break;
            }
        }
    }
}

void Scene::set(){
}

void Scene::draw(position& initial_pos,position& final_pos){
    int block_frame=int(initial_pos.x)/145;
    switch(block_frame){
        case 0:
            textures.insert(std::make_pair(std::make_pair(final_pos.x/32,final_pos.y/32), treasure));
            break;
        case 1:
            textures.insert(std::make_pair(std::make_pair(final_pos.x/32,final_pos.y/32), player));
            break;
        default:
            break;
    }
}

void Scene::render(){
    SDL_Rect Message_rect={165,608,100,80};
    SDL_Rect Message_rect4={30,630,70,70};
    SDL_Rect Message_rect3={0,608,1024,92};
    SDL_RenderCopy(window.getRenderer(), bar, NULL, &Message_rect3);
    SDL_RenderCopy(window.getRenderer(), treasure, NULL, &Message_rect4); 
    SDL_RenderCopy(window.getRenderer(), player, NULL, &Message_rect); 
    for (auto& it: tiles) {
        int x=std::get<0>(it.first);
        int y=std::get<1>(it.first);
        SDL_Rect Message_rect6={x,y,32,32};
        SDL_RenderCopy(window.getRenderer(),(it.second),NULL,&Message_rect6);
    }


    for (auto& it: textures) {
        int x=std::get<0>(it.first);
        int y=std::get<1>(it.first);
        SDL_Rect Message_rect6={x*32,y*32,32,32};
        SDL_RenderCopy(window.getRenderer(),(it.second),NULL,&Message_rect6);
    }

}

void Scene::show(){
}

Scene::~Scene(){
    
}