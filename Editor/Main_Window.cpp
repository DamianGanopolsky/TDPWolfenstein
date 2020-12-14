#include "Main_Window.h"

Main_Window::Main_Window(SdlWindow& Window):window(Window){
    SDL_Surface* main_window_surf=IMG_Load("../Editor/Editor_Assets/Completev2.jpeg");
    main_window=SDL_CreateTextureFromSurface(window.getRenderer(),main_window_surf);
}


void Main_Window::render_window(){

    float bar_coef=0.81481;
    float bar_2_coef=0.188;

    //SDL_Rect bar_rect={0,0,}
    //printf("Height es %f \n",window.getHeight());
    //printf("Resultado es %i \n",int(window.getHeight()*bar_coef));

    SDL_Rect bar_rect={0,int(window.getHeight()*bar_coef),\
   int(window.getWidth()),int(bar_2_coef*window.getHeight())};   

    /*SDL_Rect bar_rect={0,440,\
    int(window.getWidth()),100};   */

    SDL_RenderCopy(window.getRenderer(),main_window,NULL,&bar_rect);
}