#include "Scene.h"
#define PATH_TO_MAP "../Maps/"
#define EXTENSION ".yaml"


Scene::Scene(SdlWindow& Window,std::string YamlPath):window(Window),\
map(Window,YamlPath),main_window(Window),InputView(Window),map_options_view(Window){
    
}

void Scene::draw(position& initial_pos,position& final_pos){
    map.draw(initial_pos,final_pos);
}

void Scene::click(position final_pos){
    if(map_options_view.is_active()){
        YamlPathToOpen=map_options_view.Handle_Click(final_pos.x,final_pos.y);
        if(YamlPathToOpen!=PATH_TO_MAP){
            map.LoadMap(YamlPathToOpen);
            map.printMap();
        }
        map_options_view.load_textures();
    }
    else{
        if(InputView.is_active()){
            if(InputView.IsSaveButtonPressed(final_pos.x,final_pos.y)){
                std::string map_name=InputView.getMapName();
                map.Export(PATH_TO_MAP+map_name+EXTENSION);
            }
        }
        else{
            if((final_pos.y<int(0.1094*window.getHeight()))&(final_pos.x>int(0.9531*window.getWidth()))){ //HARDCODEADO
                InputView.set_active();
            }
            map.click(final_pos);
        }
    }
}

void Scene::render(){
    if(map_options_view.is_active()){
        map_options_view.render();
    }
    else{
        map.render();
        main_window.render_window();
        if(InputView.is_active()){
            InputView.render();
        }
    }
}

void Scene::HandleTextInput(SDL_Event* event){
    if(InputView.is_active()){
        InputView.Update(event);
    }
}

void Scene::HandleMovementWASD(SDL_Event* event){

    if(!InputView.is_active()){
        map.HandleMovementWASD(event);
    }
}

Scene::~Scene(){
    
}