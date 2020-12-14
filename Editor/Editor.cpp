#include "Editor.h"
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#define BAR_POS_IN_WINDOW 0.81481


Editor::Editor(SdlWindow& Window):window(Window),scene(Window),is_clicked_correctly(false),is_dragging(false){
}

void Editor::HandleMotion(SDL_Event* event){
    if(is_dragging==true){
        final_position={event->button.x,event->button.y};
        scene.draw(initial_position,final_position);
    }
}


void Editor::HandleLeftClickPress(SDL_Event* event){
    initial_position.x=int(event->button.x);
    initial_position.y=int(event->button.y);
    if(is_clicked_correctly==true){
        final_position={event->button.x,event->button.y};
        scene.draw(initial_position,final_position);
    }
}

void Editor::HandleRightClickPress(SDL_Event* event){
    if(is_clicked_correctly==true){
        is_dragging=true;
    }
    is_clicked_correctly=false;
}

void Editor::HandleRightClickRelease(SDL_Event* event){
    is_dragging=false;
    if(event->button.y>window.getHeight()*BAR_POS_IN_WINDOW){ //Falta validar en x
        initial_position.x=int(event->button.x);
        initial_position.y=int(event->button.y);
        is_clicked_correctly=true;
    }
}

void Editor::HandleLeftClickRelease(SDL_Event* event){
    final_position={event->button.x,event->button.y};
    if((initial_position.x!=int(event->button.x))||(initial_position.y!=int(event->button.y))){
        scene.draw(initial_position,final_position);
        is_clicked_correctly=false;
    }
}

void Editor::HandleMovementWASD(SDL_Event* event){
    scene.HandleMovementWASD(event);
}

void Editor::render(){
    scene.render();
}

Editor::~Editor(){

}