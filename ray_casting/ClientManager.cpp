#include "ClientManager.h"
#include "../Common/blocking_queue.h"
#include "../Common/non_blocking_queue.h"
#include "ClientConnector/UpdateMessage.h"
#include "ClientConnector/Command.h"
#include "../Common/protocol.h"
#include "ConstantRateLoop_.h"

ClientManager::ClientManager(std::string Host,std::string Port):host(Host),port(Port){
	if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,1024)<0){
        throw std::invalid_argument("Error  en la inicializacion del audio \n");
    }

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        throw std::invalid_argument("Error en la inicializacion de sdl \n");
	}
    TTF_Init();
}


void ClientManager::start(){
	/* TENGO QUE RECIBIR EL PLAYER Y EL MAP ANTES QUE NADA, */
	std::cout << "Host:" << host << "Port:" << port << std::endl;
	NonBlockingQueue<UpdateMessage*> recv_queue;
	ClientSocket clientsock(recv_queue,host.c_str(),port.c_str());
	New_Player_Event player_info=clientsock.recv_player();
	Player player(player_info);
	Map_2d map(player,"../Maps/Fortified_6.yaml");
	Panel_window panel(map);
	BlockingQueue<Command*> send_queue;
	
	Player_handler handler(player,map,send_queue);
	Client client(panel,player,map);
	
	ReceiveController receivecontroller(player,map,recv_queue,client);
	Receiver receiver(&clientsock,recv_queue,receivecontroller);
	Sender sender(&clientsock,send_queue);
	receiver.start();
	sender.start();
	
	MusicSoundtrack music;
	music.play_editor();
	//ConstantRateLoop_ crl(handler,client,receivecontroller);
	//crl.run();

	bool is_running=true;

    while (is_running) {
		//client.render();
		receivecontroller.update();    //Recibo eventos y actualizo
		is_running=handler.handle();   //Capturo eventos del cliente y envio
		
	}
	sender.stop();
	sender.join();
    receiver.stop();
	receiver.join();  
}

ClientManager::~ClientManager(){
    Mix_CloseAudio();
    SDL_Quit();
}