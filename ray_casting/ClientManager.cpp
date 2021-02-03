#include "ClientManager.h"
#include "../Common/blocking_queue.h"
#include "../Common/non_blocking_queue.h"
#include "ClientConnector/UpdateMessage.h"
#include "ClientConnector/Command.h"

ClientManager::ClientManager(){
	if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,1024)<0){
        throw std::invalid_argument("Error  en la inicializacion del audio \n");
    }

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        throw std::invalid_argument("Error en la inicializacion de sdl \n");
	}
    TTF_Init();
}


void ClientManager::start(){
	ClientSocket clientsock;
	BlockingQueue<Command*> send_queue;
	NonBlockingQueue<UpdateMessage*> recv_queue;
	Receiver receiver(&clientsock,recv_queue);
	Sender sender(&clientsock,send_queue);
	sender.start();
	Player player(100, 100, 270);
	Map_2d map(player);
	//Pruebas de concepto
	
	receiver.start();
	Panel_window panel(map);
	Player_handler handler(player,map,send_queue);
	Client client(panel,player,map);
	ReceiveController receivecontroller(player,map,recv_queue,client);
	MusicSoundtrack music;
	music.play_editor();
	client.render();
	receivecontroller.start();
	bool quit=false;

    while (!quit) {
		//client.render();
		quit=receivecontroller.start();    //Recibo eventos y actualizo
		quit=handler.handle();   //Capturo eventos del cliente y envio
		//receivecontroller.ExecuteEvent();
	}
	sender.stop();
	//sender.join();
    receiver.stop();
	//receiver.join();  
}

ClientManager::~ClientManager(){
    Mix_CloseAudio();
    SDL_Quit();
}