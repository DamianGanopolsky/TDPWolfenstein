#include "Panel_window.h"
#include "Player.h"
#include "Player_info.h"
//#include "Event_handler.h"
#include "Map_2d.h"
#include "Game_element.h"
#include "Ray.h"
#include "Constant_rate_loop.h"
#include "Player_handler.h"

#include "Client.h"

#include <utility>
#include <set>
#include <list>
#include <unistd.h>
#include <iostream>

int main() {
	Player player(128, 341, 90);
	
	Panel_window panel;
	
	Map_2d map(player);
	//Event_handler handler;
	Player_handler handler(player);
	Client client(panel,player,map);
	//handler.handle(player);
	client.render();
	//Constant_rate_loop crl(100);
	/*
	std::set<Ray> rays = std::move(map.get_player_rays());
	std::list<Game_element> elements = std::move(map.get_game_elements());
	panel.update(std::move(rays), std::move(elements),  player.get_info());
	crl.task_finished();  */
	bool quit=false;
	

	while (!quit) {
		//std::set<Ray> rays = std::move(map.get_player_rays());
		//std::list<Game_element> elements = std::move(map.get_game_elements());
		//panel.update(std::move(rays), std::move(elements),  player.get_info());
		//crl.task_finished();  
		client.render();
		quit=handler.handle();
	}
	/*std::set<Ray> rays2 = std::move(map.get_player_rays());
	std::list<Game_element> elements2 = std::move(map.get_game_elements());
	panel.update(std::move(rays2), std::move(elements2),  player.get_info());
	crl.task_finished(); */
	//sleep(10); 
	return 0;
}


