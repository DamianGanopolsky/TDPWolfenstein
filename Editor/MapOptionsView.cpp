#include "MapOptionsView.h"
#include <sys/types.h>
#include <dirent.h>
#define PATH_TO_MAP "../Maps/"

void MapOptionsView::load_textures(){
    int count=3;
    for(std::vector<std::string>::iterator it = files.begin(); it != files.end(); ++it) {

        if((*it).size()<4) continue;
        map_buttons.push_back(MapButton(window,{int(0.1042*window.getWidth())\
        ,int(count*0.0703*window.getHeight()),int((*it).size()*0.010417*window.getWidth())\
        ,int(0.0625*window.getHeight())},*it));
        count++;
    }
}

MapOptionsView::MapOptionsView(SdlWindow& Window):window(Window),active(true){
    SDL_Surface* main_screen_surf=IMG_Load("../Editor/Editor_Assets/Mapas_Main_Screen.png");
    main_screen=SDL_CreateTextureFromSurface(window.getRenderer(),main_screen_surf);
    std::string directory_path=PATH_TO_MAP;
    DIR* dirp = opendir(directory_path.c_str());
    struct dirent * dp;
    while ((dp = readdir(dirp)) != NULL) {
        files.push_back(dp->d_name);
    }
    closedir(dirp);
    load_textures();
}



bool MapOptionsView::is_active(){
    return active;
}

std::string MapOptionsView::Handle_Click(int x,int y){
    std::string file_chosen=PATH_TO_MAP;
    for(std::vector<MapButton>::iterator it = map_buttons.begin(); it != map_buttons.end(); ++it) {
        if((*it).is_clicked(x,y)){
            file_chosen+=(*it).get_file_name();
            active=false;
        }
    }
    return file_chosen;
}

void MapOptionsView::render(){
    
    SDL_Rect main_screen_rect={0,0,int(window.getWidth()),int(window.getHeight())};
    SDL_SetRenderDrawColor(window.getRenderer(), 128, 128, 128, 255);
    SDL_RenderCopy(window.getRenderer(),main_screen,NULL,&main_screen_rect);

    for(std::vector<MapButton>::iterator it = map_buttons.begin(); it != map_buttons.end(); ++it) {
        (*it).render();
    }
}