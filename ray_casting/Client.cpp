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
        elements = std::move(map.get_game_elements());   //No tienen que ver con lo grafico
        //DIBUJAR
        panel.update(std::move(rays), std::move(elements),  player.get_info()); 
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