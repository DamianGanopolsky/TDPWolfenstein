#include "InputTextView.h"
#include <iostream>

InputTextView::InputTextView(SdlWindow& Window):texto(Window.getRenderer()\
,255,255,255),window(Window){
    textbox.box_content="";
    textbox.active=false;
    textbox.box.x=0.3156*window.getWidth();
    textbox.box.y=0.4359*window.getHeight();
    textbox.box.w=0;
    textbox.box.h=45;
    SDL_Surface* save_menu=IMG_Load("../Editor/Editor_Assets/MenuGuardar.png");
    save_menu_texture=SDL_CreateTextureFromSurface(window.getRenderer(),save_menu);
}

void InputTextView::Update(SDL_Event* event){
    if(event->type==SDL_KEYDOWN){
        if(!textbox.box_content.empty()){
            textbox.box_content.pop_back();
            textbox.box.w -= 40;
        }
    }
    else{
        /* Si no se llego al maximo de caracteres disponibles */
        if(!(textbox.box_content.length()>9)){
            textbox.box_content += event->text.text;
            textbox.box.w += 40;
        }

    }
    texto.Load_Text("../OpenSans-Bold.ttf",textbox.box_content,12);
    texture_of_text = SDL_CreateTextureFromSurface(window.getRenderer(), texto.getSurface()); 
}

void InputTextView::render(){
    SDL_Rect Base_rect={int(0.2604*window.getWidth()),int(0.3125*window.getHeight()),\
    int(0.5208*window.getWidth()),int(0.3906*window.getHeight())};
    //SDL_Rect Text_rect={303,279,382,45};
    //SDL_Rect Text_rect={303,279,40,45};
    
    SDL_RenderCopy(window.getRenderer(),save_menu_texture,NULL,&Base_rect);
    SDL_RenderCopy(window.getRenderer(), texture_of_text, NULL, &textbox.box); 

}

bool InputTextView::IsSaveButtonPressed(int x,int y){
    textbox.active=false;
    if(((x>0.5437*window.getWidth())&&(x<0.6927*window.getWidth()))\
    &&(y>0.5344*window.getHeight())&&(y<0.6062*window.getHeight())){
        std::cout << "Presione el boton guardar" << std::endl;
        return true;
    }
    else{
        return false;
    }
    return true;
}

std::string InputTextView::getMapName(){
    return textbox.box_content;
}

bool InputTextView::is_active(){
    return textbox.active;
}

void InputTextView::set_active(){
    textbox.active=true;
}