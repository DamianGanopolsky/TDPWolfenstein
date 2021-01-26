#include "Scene.h"
#define PATH_TO_MAP "../Maps/"
#define EXTENSION ".yaml"


Scene::Scene(SdlWindow& Window,std::string YamlPath):window(Window),\
map(Window,YamlPath),main_window(Window),InputView(Window){
    
}

void Scene::draw(position& initial_pos,position& final_pos){
    map.draw(initial_pos,final_pos);
}

void Scene::click(position final_pos){
    if(InputView.is_active()){
        if(InputView.IsSaveButtonPressed(final_pos.x,final_pos.y)){
            std::string map_name=InputView.getMapName();
            map.Export(PATH_TO_MAP+map_name+EXTENSION);
        }
    }
    else{
        if((final_pos.y<int(0.1094*window.getHeight()))&(final_pos.x>int(0.9531*window.getWidth()))){ //HARDCODEADO
            InputView.set_active();
            //map.render();
        }
        map.click(final_pos);
    }
}

void Scene::render(){
    
    map.render();
    main_window.render_window();
    if(InputView.is_active()){
        InputView.render();
    }
}

void Scene::HandleTextInput(SDL_Event* event){
    if(InputView.is_active()){
        InputView.Update(event);
    }
}
/*
void Scene::HandleKeyPressed(SDL_Event* event){
    if(InputView.is_active()){
        //Visualizo el texto
        std::cout << event->text.text << std::endl;
        InputView.Update(event);
        std::cout << "IS active" << std::endl;
    }
    else{
        map.HandleMovementWASD(event);
    }
}*/

void Scene::HandleMovementWASD(SDL_Event* event){

    if(!InputView.is_active()){
        map.HandleMovementWASD(event);
    }
}
/*
void Scene::SaveMap(std::string PathToFile){
    InputView.set_active();
    //map.Export(PathToFile);
}
*/
Scene::~Scene(){
    
}