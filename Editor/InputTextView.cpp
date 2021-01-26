#include "InputTextView.h"
#include <iostream>

InputTextView::InputTextView(SdlWindow& Window):texto(Window.getRenderer()\
,255,255,255),window(Window){
    textbox.box_content="";
    textbox.active=false;
    SDL_Surface* save_menu=IMG_Load("../Editor/Editor_Assets/MenuGuardar.png");
    save_menu_texture=SDL_CreateTextureFromSurface(window.getRenderer(),save_menu);
}

void InputTextView::Update(SDL_Event* event){
    textbox.box_content += event->text.text;
    texto.Load_Text("../OpenSans-Bold.ttf",textbox.box_content,12);
    texture_of_text = SDL_CreateTextureFromSurface(window.getRenderer(), texto.getSurface()); 
}

void InputTextView::render(){
    SDL_Rect Base_rect={250,200,500,250};
    SDL_Rect Text_rect={303,279,382,45};
    
    SDL_RenderCopy(window.getRenderer(),save_menu_texture,NULL,&Base_rect);
    SDL_RenderCopy(window.getRenderer(), texture_of_text, NULL, &Text_rect); 

}

bool InputTextView::is_active(){
    return textbox.active;
}

void InputTextView::set_active(){
    textbox.active=true;
}