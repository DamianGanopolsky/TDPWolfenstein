#include "Client.h"
#include <iostream>
#include <unistd.h>

Client::Client(Panel_window& Panel,Player& Player,Map_2d& Map):panel(Panel),player(Player),map(Map),\
player_lost_(false),game_finished(false),waiting_screen(true){
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

void Client::start_game(){
    waiting_screen=false;
}

bool Client::is_playing(){
    return !waiting_screen;
}

void Client::render(){
    //auto t1= std::chrono::steady_clock::now();
    //int animation_to_render=0;
    if(waiting_screen){
        panel.render_waiting_screen();
        return;
    }

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

void Client::stop_game(std::vector<Player_stats> Final_Stats){
    game_finished=true;
    final_stats=Final_Stats;
}

Player Client::get_player(){
    return player;
}