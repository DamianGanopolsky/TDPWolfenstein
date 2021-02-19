#include "Client.h"
#include <iostream>
#include <unistd.h>

Client::Client(Panel_window& Panel,Player& Player,Map_2d& Map):panel(Panel),player(Player),map(Map),\
player_lost_(false),game_finished(false){
    rays = std::move(map.get_player_rays());
    elements = std::move(map.get_game_elements());
    panel.update(std::move(rays), std::move(elements),  player.get_info());
}

void Client::update(){
    rays = std::move(map.get_player_rays());   //No tienen que ver con lo grafico
    //Todos los elementos que no son paredes. Tienen que tener una distancia
    elements = std::move(map.get_game_elements());   //No tienen que ver con lo grafico
    panel.update(std::move(rays), std::move(elements),  player.get_info()); 
}

void Client::render(){
    //auto t1= std::chrono::steady_clock::now();
    //int animation_to_render=0;
    if((!player_lost_)&&(!game_finished)){
        
        rays = std::move(map.get_player_rays());   //No tienen que ver con lo grafico
        //Todos los elementos que no son paredes. Tienen que tener una distancia

        auto t1=std::chrono::steady_clock::now();
        elements = std::move(map.get_game_elements());   //No tienen que ver con lo grafico
        auto t2= std::chrono::steady_clock::now();
        std::chrono::duration<float, std::milli> diff;
			//std::chrono::duration<double> diff=t2-t1;
        diff = t2 - t1;
        std::cout << "DELTA DE GET ELEMENTS ES" << diff.count() << std::endl;
        //DIBUJAR
        t1=std::chrono::steady_clock::now();

        panel.update(std::move(rays), std::move(elements),  player.get_info()); 
        t2= std::chrono::steady_clock::now();
       // std::chrono::duration<float, std::milli> diff;
			//std::chrono::duration<double> diff=t2-t1;
        diff = t2 - t1;
        std::cout << "DELTA DE RENDERIZADO POSTA ES" << diff.count() << std::endl;
    }
    else{
        if(game_finished){
            panel.render_ending_screen();
        }
        else{
            panel.render_player_lost_screen();
        }
    }
}

void Client::player_lost(){
    player_lost_=true;
}

void Client::stop_game(){
    game_finished=true;
}

Player Client::get_player(){
    return player;
}