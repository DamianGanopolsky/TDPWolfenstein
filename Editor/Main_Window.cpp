#include "Main_Window.h"
#include <iostream>

Main_Window::Main_Window(SdlWindow& Window):window(Window){
    SDL_Surface* main_window_surf=IMG_Load("../Editor/Editor_Assets/final_barra.jpeg");
    main_window=SDL_CreateTextureFromSurface(window.getRenderer(),main_window_surf);
    SDL_Surface* save_button_surf=IMG_Load("../Editor/Editor_Assets/Save_Button.png");
    save_button=SDL_CreateTextureFromSurface(window.getRenderer(),save_button_surf);
    //SDL_Surface* expand_surf=IMG_Load("../Editor/Editor_Assets/tamaño_con_bg.jpeg");
    //tools=SDL_CreateTextureFromSurface(window.getRenderer(),expand_surf);
}


void Main_Window::render_window(){

    float bar_coef=0.81481;
    float bar_2_coef=0.188;

    float save_x_coef=0.9;
    float save_x_coef_delta=0.05;
    float save_y_coef_delta=0.1;

    //SDL_Rect tools_rect={0,0,720,100};
    

    SDL_Rect bar_rect={0,int(window.getHeight()*bar_coef),\
    int(window.getWidth()),int(bar_2_coef*window.getHeight())};  

    SDL_Rect save_rect={int(window.getWidth()*save_x_coef),0,\
    int(save_x_coef_delta*window.getWidth()),int(save_y_coef_delta*window.getHeight())};  

    SDL_RenderCopy(window.getRenderer(),main_window,NULL,&bar_rect);
    SDL_RenderCopy(window.getRenderer(),save_button,NULL,&save_rect);
    //SDL_RenderCopy(window.getRenderer(),tools,NULL,&tools_rect);
}