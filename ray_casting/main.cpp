#include "Panel_window.h"
#include "Player.h"
#include "Player_info.h"
//#include "Event_handler.h"
#include "Player_handler.h"

#include "Client.h"
#include <iostream>

int main() {
	Player player(128, 341, 90);
	Panel_window panel;
	Map_2d map(player);
	Player_handler handler(player);
	Client client(panel,player,map);
	client.render();
	bool quit=false;
	
	while (!quit) {
		client.render();
		quit=handler.handle();
	}
	return 0;
}


