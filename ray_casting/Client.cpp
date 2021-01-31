#include "Client.h"
#include <iostream>

Client::Client(Panel_window& Panel,Player& Player,Map_2d& Map):panel(Panel),player(Player),map(Map){
    rays = std::move(map.get_player_rays());
    elements = std::move(map.get_game_elements());
    panel.update(std::move(rays), std::move(elements),  player.get_info());

}

void Client::render(){
    
    rays = std::move(map.get_player_rays());   //No tienen que ver con lo grafico
    //Todos los elementos que no son paredes. Tienen que tener una distancia
    elements = std::move(map.get_game_elements());   //No tienen que ver con lo grafico
    //DIBUJAR
    panel.update(std::move(rays), std::move(elements),  player.get_info()); 
}

Player Client::get_player(){
    return player;
}