#include "Scene.h"


Scene::Scene(SdlWindow& Window,std::string YamlPath):window(Window),map(Window,YamlPath),main_window(Window){
}

void Scene::draw(position& initial_pos,position& final_pos){
    map.draw(initial_pos,final_pos);
}

void Scene::click(position final_pos){
    map.click(final_pos);
}

void Scene::render(){
    
    map.render();
    main_window.render_window();
}

void Scene::HandleMovementWASD(SDL_Event* event){
    map.HandleMovementWASD(event);
}

Scene::~Scene(){
    
}