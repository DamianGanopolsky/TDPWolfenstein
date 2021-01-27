#include "MapOptionsView.h"
#include <sys/types.h>
#include <dirent.h>

void MapOptionsView::load_textures(){
    int count=0;
    for(std::vector<std::string>::iterator it = files.begin(); it != files.end(); ++it) {

        std::cout << *it << std::endl;
        SdlText texto(window.getRenderer(),255,255,255);
        //SDL_Rect rect={count*40,count*40,100,40};
        texto.Load_Text("../OpenSans-Bold.ttf",*it,12);
        positions.push_back({count*40,count*40,100,40});
        textures_of_files.push_back(SDL_CreateTextureFromSurface(window.getRenderer(), texto.getSurface())); 
        count++;
    }
}

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
    load_textures();

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

    //SDL_Rect rect2={250,250,250,250};

    //SDL_Rect rect={100,100,100,100};
    SDL_SetRenderDrawColor(window.getRenderer(), 128, 128, 128, 255);
    SDL_RenderCopy(window.getRenderer(),main_screen,NULL,&main_screen_rect);
    int count=0;

    for(std::vector<SDL_Texture*>::iterator it = textures_of_files.begin(); it != textures_of_files.end(); ++it) {

        SDL_RenderCopy(window.getRenderer(),textures_of_files.at(count),NULL,&positions.at(count));

        count++;
    }

    //SDL_RenderCopy(window.getRenderer(),textures_of_files.at(1),NULL,&rect);
    //SDL_RenderCopy(window.getRenderer(),textures_of_files.at(4),NULL,&rect2);
}