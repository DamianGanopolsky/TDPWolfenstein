#include "MapOptionsView.h"
#include <sys/types.h>
#include <dirent.h>

MapOptionsView::MapOptionsView(SdlWindow& Window):window(Window),active(true){
    SDL_Surface* main_screen_surf=IMG_Load("../Editor/Editor_Assets/Mapas_Main_Screen.png");
    main_screen=SDL_CreateTextureFromSurface(window.getRenderer(),main_screen_surf);
    std::string directory_path="../Maps";
    DIR* dirp = opendir(directory_path.c_str());
    struct dirent * dp;
    while ((dp = readdir(dirp)) != NULL) {
        files.push_back(dp->d_name);
    }
    closedir(dirp);

}

void MapOptionsView::load_textures(){

    for(std::vector<std::string>::iterator it = files.begin(); it != files.end(); ++it) {
        SdlText texto(window.getRenderer(),255,255,255);
        texto.Load_Text("../OpenSans-Bold.ttf",*it,12);
        textures_of_files.push_back(SDL_CreateTextureFromSurface(window.getRenderer(), texto.getSurface()));
        //texture_of_text = SDL_CreateTextureFromSurface(window.getRenderer(), texto.getSurface()); 
        std::cout << *it << std::endl;
    }
}

bool MapOptionsView::is_active(){
    return true;
}

void MapOptionsView::Handle_Click(int x,int y){

    for(std::vector<std::string>::iterator it = files.begin(); it != files.end(); ++it) {
        std::cout << *it << std::endl;
    }

}

void MapOptionsView::render(){
    
    SDL_Rect main_screen_rect={0,0,960,640};
    SDL_SetRenderDrawColor(window.getRenderer(), 128, 128, 128, 255);
    SDL_RenderCopy(window.getRenderer(),main_screen,NULL,&main_screen_rect);
}