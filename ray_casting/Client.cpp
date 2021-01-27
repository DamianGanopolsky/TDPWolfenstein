#include "Client.h"
#include <iostream>

Client::Client(Panel_window& Panel,Player& Player,Map_2d& Map):panel(Panel),player(Player),map(Map){
    rays = std::move(map.get_player_rays());
    elements = std::move(map.get_game_elements());
    panel.update(std::move(rays), std::move(elements),  player.get_info());

}

void Client::render(){
    //DIBUJAR
    rays = std::move(map.get_player_rays());
    elements = std::move(map.get_game_elements());
    panel.update(std::move(rays), std::move(elements),  player.get_info()); 
}

Player Client::get_player(){
    return player;
}