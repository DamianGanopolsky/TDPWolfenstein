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
#include "ClientConnector/ReceiveController.h"

#include "../Common/blocking_queue.h"

#include "Client.h"
#include <iostream>


int main() {
	
	
	if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,1024)<0){
        std::cout << "eRROR:" << Mix_GetError() << std::endl;
    }
	//Pruebas de concepto
	ClientSocket clientsock;
	Receiver receiver(&clientsock);
	Sender sender(&clientsock);
	sender.start();
	sender.send(4);
	receiver.start();
	//BlockingQueue blqueue;

	Player player(100, 100, 90);
	Map_2d map(player);

	//Pruebas de concepto
	ReceiveController receivecontroller(player,map);
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
		receivecontroller.ExecuteEvent();
	}
	//Pruebas de concepto
	sender.stop();
	sender.join();
	receiver.stop();
	receiver.join();

	return 0;
}


