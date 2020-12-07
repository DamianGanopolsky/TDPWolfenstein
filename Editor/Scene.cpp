#include "Scene.h"

Scene::Scene(SdlWindow& Window):window(Window),map(Window){
    SDL_Surface* tre_surface=IMG_Load("../Editor/Treasure.png");
    treasure=SDL_CreateTextureFromSurface(window.getRenderer(),tre_surface);
    SDL_Surface* player_surface = IMG_Load("../prueba_mapa/assets/imagen1.png");
    player=SDL_CreateTextureFromSurface(window.getRenderer(),player_surface);
    SDL_Surface* bar_surface=IMG_Load("../Editor/Barra2.png");
    bar=SDL_CreateTextureFromSurface(window.getRenderer(),bar_surface);
    SDL_Surface* floor_tile_surf=IMG_Load("../Editor/Barra2.png");
    floor_tile=SDL_CreateTextureFromSurface(window.getRenderer(),floor_tile_surf);
}

void Scene::draw_initial_map(int **level){
    /*
    Level=level;
    for(int i=0;i<36;i++){
        for(int j=0;j<21;j++){
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
    */
}

void Scene::set(){
}

void Scene::draw(position& initial_pos,position& final_pos){
    //int block_frame=int(initial_pos.x)/145;
    map.draw(initial_pos,final_pos);
    /*
    int block_frame=int(initial_pos.x)/145;
    switch(block_frame){
        case 0:
            Level[final_pos.x/32][final_pos.y/32]=1;
            textures.insert(std::make_pair(std::make_pair(final_pos.x/32,final_pos.y/32), treasure));
            break;
        case 1:
            textures.insert(std::make_pair(std::make_pair(final_pos.x/32,final_pos.y/32), player));
            break;
        default:
            break;
    }
    */
}

void Scene::render(){
    /*
    for (auto& it: tiles) {
        int x=std::get<0>(it.first);
        int y=std::get<1>(it.first);
        SDL_Rect Floor_rect={x,y,32,32};
        SDL_RenderCopy(window.getRenderer(),(it.second),NULL,&Floor_rect);
    }
    for (auto& it: textures) {
        int x=std::get<0>(it.first);
        int y=std::get<1>(it.first);
        SDL_Rect Message_rect6={x*32,y*32,32,32};
        SDL_RenderCopy(window.getRenderer(),(it.second),NULL,&Message_rect6);
    } */
    
    map.render();
    SDL_Rect Player_rect={165,608,100,80};
    SDL_Rect Treasure_rect={30,630,70,70};
    SDL_Rect Bar_rect={0,608,1024,92};
    SDL_RenderCopy(window.getRenderer(), bar, NULL, &Bar_rect);
    SDL_RenderCopy(window.getRenderer(), treasure, NULL, &Treasure_rect); 
    SDL_RenderCopy(window.getRenderer(), player, NULL, &Player_rect); 
}

void Scene::HandleMovementWASD(SDL_Event* event){
    map.HandleMovementWASD(event);
}

void Scene::show(){
}

Scene::~Scene(){
    
}