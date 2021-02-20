#include "TextButton.h"
#include <iostream>

TextButton::TextButton(SDL_Renderer*& Renderer):renderer(Renderer){
   // TTF_Init();
    
    //for(int i=0;i<13;i++){
      //  caracteres.push_back(SdlText(Renderer,255,255,255));
   // }
    textbox.box_content="";
    textbox.active=false;
    /*textbox.box.x=0.28*window.getWidth();

    textbox.box.y=0.4359*window.getHeight();
    textbox.box.w=int(0.04166*window.getWidth());
    textbox.box.h=int(0.0703*window.getHeight());*/
    std::cout << "ASD" << std::endl;
    SDL_Surface* button_base_surface=IMG_Load("../ray_casting/sprites/Unpressed_bar.png");
    button_base=SDL_CreateTextureFromSurface(Renderer,button_base_surface);
}


void TextButton::render(){
    /*SDL_Rect Base_rect={int(0.2604*window.getWidth()),int(0.3125*window.getHeight()),\
    int(0.5208*window.getWidth()),int(0.3906*window.getHeight())};*/
    SDL_Rect Base_rect={int(0.34*PANEL_WIDTH),int(0.505*PANEL_HEIGHT),\
    int(0.29*PANEL_WIDTH),int(0.12*PANEL_HEIGHT)};
    //int x_base=0.235*PANEL_WIDTH;;
    //int count=0;
    std::string aux;
    SDL_RenderCopy(renderer,button_base,NULL,&Base_rect);
    /*
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
    }*/
    //SDL_RenderCopy(window.getRenderer(), texture_of_text, NULL, &textbox.box); 
}