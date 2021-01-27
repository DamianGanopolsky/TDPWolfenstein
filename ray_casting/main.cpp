#include "Panel_window.h"
#include "Player.h"
#include "Player_info.h"
//#include "Event_handler.h"
#include "Player_handler.h"

#include "MusicSoundtrack.h"

#include "Client.h"
#include <iostream>


int main() {
	
	Panel_window panel;
	
	std::cout << "ok" << std::endl;
	if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,1024)<0){
        std::cout << "eRROR:" << Mix_GetError() << std::endl;
    }
	Player player(128, 341, 90);
	Map_2d map(player);
	
	Player_handler handler(player);
	Client client(panel,player,map);
	//MusicSoundtrack music;
	//music.play_editor();
	SdlSound sonido("../Sounds/SS_Agent_death.wav");
	sonido.play(128);
	client.render();
	bool quit=false;

	
	while (!quit) {
		client.render();
		quit=handler.handle();
	}
	return 0;
}


