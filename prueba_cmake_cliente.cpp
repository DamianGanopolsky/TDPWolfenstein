#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "Prueba_sonido.h"

int main(int argc,char* argv[]){

    std::cout << "Archivo a compilar por cmake" << std::endl;
    Prueba_sonido sonido;
    sonido.sounds_init();
    sonido.load_sound("../Sounds/SS_Agent_death.wav");
    sonido.play();

    return 0;
}