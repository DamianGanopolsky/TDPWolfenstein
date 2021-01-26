#include "Main_Window.h"
#include <iostream>

Main_Window::Main_Window(SdlWindow& Window):window(Window){
    SDL_Surface* main_window_surf=IMG_Load("../Editor/Editor_Assets/final_barra.jpeg");
    main_window=SDL_CreateTextureFromSurface(window.getRenderer(),main_window_surf);
    SDL_Surface* save_button_surf=IMG_Load("../Editor/Editor_Assets/Save_Button.png");
    save_button=SDL_CreateTextureFromSurface(window.getRenderer(),save_button_surf);
}


void Main_Window::render_window(){

    float bar_coef=0.81481;
    float bar_2_coef=0.188;

    float save_x_coef=0.9375;
    float save_x_coef_delta=0.0729;
    float save_y_coef_delta=0.1094;

    SDL_Rect bar_rect={0,int(window.getHeight()*bar_coef),\
    int(window.getWidth()),int(bar_2_coef*window.getHeight())};  
    
    SDL_Rect save_rect={int(save_x_coef*window.getWidth()),0,\
    int(save_x_coef_delta*window.getWidth()),int(save_y_coef_delta*window.getHeight())};

    SDL_RenderCopy(window.getRenderer(),main_window,NULL,&bar_rect);
    SDL_RenderCopy(window.getRenderer(),save_button,NULL,&save_rect);
}