#include "Panel_window.h"
#include "Player.h"
#include "Player_info.h"
//#include "Event_handler.h"
#include "Player_handler.h"
#include "ClientConnector/Receiver.h"
#include "ClientConnector/Sender.h"
#include "ClientConnector/ClientSocket.h"


#include "SdlClasses/MusicSoundtrack.h"
#include "../Common/thread.h"

#include "Client.h"
#include <iostream>


int main() {
	
	
	if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,1024)<0){
        std::cout << "eRROR:" << Mix_GetError() << std::endl;
    }

	ClientSocket clientsock;
	Receiver receiver;
	Sender sender(&clientsock);
	sender.start();
	sender.send(4);

	receiver.start();
	Player player(100, 100, 90);
	Map_2d map(player);
	Panel_window panel(map);
	
	Player_handler handler(player,map);
	Client client(panel,player,map);
	MusicSoundtrack music;
	music.play_editor();
	client.render();
	bool quit=false;

	
	while (!quit) {
		client.render();
		quit=handler.handle();
	}
	sender.stop();
	sender.join();
	receiver.stop();
	receiver.join();
	return 0;
}


