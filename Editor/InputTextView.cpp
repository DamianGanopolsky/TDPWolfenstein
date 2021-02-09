#include "InputTextView.h"
#include <iostream>
#include "yaml-cpp/yaml.h"

InputTextView::InputTextView(SdlWindow& Window):texto(Window.getRenderer()\
,255,255,255),window(Window){
    TTF_Init();
    for(int i=0;i<13;i++){
        caracteres.push_back(SdlText(window.getRenderer(),255,255,255));
    }
    YAML::Node config = YAML::LoadFile("../Yaml_configs/editor_config.yaml");
    max_length_file = config["max_length_file"].as<size_t>();
    textbox.box_content="";
    textbox.active=false;
    //textbox.box.x=0.3156*window.getWidth();
    textbox.box.x=0.28*window.getWidth();

    textbox.box.y=0.4359*window.getHeight();
    //textbox.box.y=0.41*window.getHeight();

    //textbox.box.w=40;
    textbox.box.w=int(0.04166*window.getWidth());
    textbox.box.h=int(0.0703*window.getHeight());

    //textbox.box.h=45;
    SDL_Surface* save_menu=IMG_Load("../Editor/Editor_Assets/MenuGuardar.png");
    save_menu_texture=SDL_CreateTextureFromSurface(window.getRenderer(),save_menu);
}

void InputTextView::Update(SDL_Event* event){
    if(event->type==SDL_KEYDOWN){
        if(!textbox.box_content.empty()){
            textbox.box_content.pop_back();
            //textbox.box.w -= 40;
        }
    }
    else{
        /* Si no se llego al maximo de caracteres disponibles */
        if(!(textbox.box_content.length()>max_length_file)){
            textbox.box_content += event->text.text;
            //textbox.box.w += 40;
        }
    }
    
    /*int count=0;
    std::string aux;
    for(char& c : textbox.box_content) {
        aux=c;
        caracteres.at(count).Load_Text("../OpenSans-Bold.ttf",aux.c_str(),12);
        std::cout << c << std::endl;
        texture_of_caracter.push_back(SDL_CreateTextureFromSurface\
        (window.getRenderer(), caracteres.at(count).getSurface()));
        count++;
    }*/
    texto.Load_Text("../OpenSans-Bold.ttf",textbox.box_content,12);
    texture_of_text = SDL_CreateTextureFromSurface(window.getRenderer(), texto.getSurface()); 
}

void InputTextView::render(){
    /*SDL_Rect Base_rect={int(0.2604*window.getWidth()),int(0.3125*window.getHeight()),\
    int(0.5208*window.getWidth()),int(0.3906*window.getHeight())};*/
    SDL_Rect Base_rect={int(0.2*window.getWidth()),int(0.3125*window.getHeight()),\
    int(0.7*window.getWidth()),int(0.3906*window.getHeight())};
    int x_base=0.235*window.getWidth();;
    int count=0;
    std::string aux;
    SDL_RenderCopy(window.getRenderer(),save_menu_texture,NULL,&Base_rect);
    for(char& c : textbox.box_content) {
        aux=c;
        caracteres.at(count).Load_Text("../OpenSans-Bold.ttf",aux.c_str(),12);
        x_base += 0.04167*window.getWidth();
        textbox.box.x = x_base;
        SDL_Texture* texture_of_char=SDL_CreateTextureFromSurface(window.getRenderer(), caracteres.at(count).getSurface());
        SDL_RenderCopy(window.getRenderer(),texture_of_char,NULL,&textbox.box);
        caracteres.at(count).close_font();
        SDL_FreeSurface(caracteres.at(count).getSurface());
	    SDL_DestroyTexture(texture_of_char);
        count++;
    }
    //SDL_RenderCopy(window.getRenderer(), texture_of_text, NULL, &textbox.box); 
}

bool InputTextView::IsSaveButtonPressed(int x,int y){
    textbox.active=false;
    /*if(((x>0.5437*window.getWidth())&&(x<0.6927*window.getWidth()))\
    &&(y>0.5344*window.getHeight())&&(y<0.6062*window.getHeight())){*/
    if(((x>0.5781*window.getWidth())&&(x<0.7813*window.getWidth()))\
    &&(y>0.5344*window.getHeight())&&(y<0.6062*window.getHeight())){
        return true;
    }
    else{
        return false;
    }
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