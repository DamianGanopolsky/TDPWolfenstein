#include "Main_Window.h"

Main_Window::Main_Window(SdlWindow& Window):window(Window){
    SDL_Surface* tre_surface=IMG_Load("../Assets/Trophy.png");
    trophy=SDL_CreateTextureFromSurface(window.getRenderer(),tre_surface);
    SDL_Surface* player_surface = IMG_Load("../prueba_mapa/assets/imagen1.png");
    player=SDL_CreateTextureFromSurface(window.getRenderer(),player_surface);
    SDL_Surface* bar_surface=IMG_Load("../Editor/Editor_Assets/Barra2.png");
    bar=SDL_CreateTextureFromSurface(window.getRenderer(),bar_surface);
    SDL_Surface* kit_surface=IMG_Load("../Assets/MedicalKit.png");
    medical_kit=SDL_CreateTextureFromSurface(window.getRenderer(),kit_surface);
    SDL_Surface* bullets_surface=IMG_Load("../Assets/Bullets.png");
    bullets=SDL_CreateTextureFromSurface(window.getRenderer(),bullets_surface);
    SDL_Surface* door_surface=IMG_Load("../Assets/Door.png");
    door=SDL_CreateTextureFromSurface(window.getRenderer(),door_surface);
    SDL_Surface* wall_surface=IMG_Load("../Assets/Wall.png");
    wall=SDL_CreateTextureFromSurface(window.getRenderer(),wall_surface);
    SDL_Surface* players_surface=IMG_Load("../Editor/Editor_Assets/Jugadores.png");
    players=SDL_CreateTextureFromSurface(window.getRenderer(),players_surface);
    SDL_Surface* objects_surface=IMG_Load("../Editor/Editor_Assets/Objetos.png");
    objects=SDL_CreateTextureFromSurface(window.getRenderer(),objects_surface);
    SDL_Surface* structures_surf=IMG_Load("../Editor/Editor_Assets/Estructuras.png");
    structures=SDL_CreateTextureFromSurface(window.getRenderer(),structures_surf);
}


void Main_Window::render_window(){
    /*SDL_Rect player_rect={165,608,100,80};
    SDL_Rect trophy_rect={30,630,70,70};
    SDL_Rect bar_rect={40,608,943,92};
    SDL_Rect kit_rect={305,608,100,80};
    SDL_Rect bullets_rect={460,608,100,80};
    SDL_Rect door_rect={600,608,100,80};
    SDL_Rect wall_rect={740,608,100,80};*/
    SDL_Rect players_rect={-22,600,340,110};
    SDL_Rect objects_rect={270,592,440,110};
    SDL_Rect structure_rect={720,596,220,110};
    /*SDL_RenderCopy(window.getRenderer(), bar, NULL, &bar_rect);
    SDL_RenderCopy(window.getRenderer(), trophy, NULL, &trophy_rect); 
    SDL_RenderCopy(window.getRenderer(), player, NULL, &player_rect); 
    SDL_RenderCopy(window.getRenderer(), medical_kit, NULL, &kit_rect);
    SDL_RenderCopy(window.getRenderer(), bullets, NULL, &bullets_rect); 
    SDL_RenderCopy(window.getRenderer(), door, NULL, &door_rect); 
    SDL_RenderCopy(window.getRenderer(), wall, NULL, &wall_rect); */
    SDL_RenderCopy(window.getRenderer(), players, NULL, &players_rect);
    SDL_RenderCopy(window.getRenderer(), objects, NULL, &objects_rect);
    SDL_RenderCopy(window.getRenderer(),structures,NULL,&structure_rect);
}