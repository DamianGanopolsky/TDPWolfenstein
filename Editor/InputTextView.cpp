#include "InputTextView.h"
#include <iostream>

InputTextView::InputTextView(SdlWindow& Window):texto(Window.getRenderer()\
,255,255,255),window(Window){
    textbox.box_content="";
    textbox.active=false;
}

void InputTextView::Update(SDL_Event* event){
    textbox.box_content += event->text.text;
    texto.Load_Text("../OpenSans-Bold.ttf",textbox.box_content,12);
    texture_of_text = SDL_CreateTextureFromSurface(window.getRenderer(), texto.getSurface()); 
}

void InputTextView::render(){
    SDL_Rect Message_rect={80,300,145,80};
    SDL_RenderCopy(window.getRenderer(), texture_of_text, NULL, &Message_rect); 

}

bool InputTextView::is_active(){
    return textbox.active;
}

void InputTextView::set_active(){
    textbox.active=true;
}