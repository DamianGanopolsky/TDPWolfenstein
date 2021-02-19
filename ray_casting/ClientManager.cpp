#include "ClientManager.h"
#include "../Common/blocking_queue.h"
#include "../Common/non_blocking_queue.h"
#include "ClientConnector/UpdateMessage.h"
#include "ClientConnector/Command.h"
#include "../Common/protocol.h"
#include "ConstantRateLoop_.h"
#include <chrono>
#include <unistd.h>
#define PATH_TO_MAPS "../Maps/"
#define YAML_EXTENSION ".yaml"

ClientManager::ClientManager(std::string Host,std::string Port):\
host(Host),port(Port){
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
	NonBlockingQueue<UpdateMessage*> recv_queue;
	ClientSocket clientsock(recv_queue,host.c_str(),port.c_str());
	std::string nickname="PlayerName";
	clientsock.send_nickname(nickname);
	New_Player_Event player_info=clientsock.recv_player();
	//std::cout << "Mapa que tengo que abrir es " << player_info.map << std::endl;
	Player player(player_info);
	Map_2d map(player,PATH_TO_MAPS+player_info.map+YAML_EXTENSION);
	Panel_window panel;
	BlockingQueue<Command*> send_queue;
	panel.load_map_dimentions(map.get_height(),map.get_width());
	Client client(panel,player,map);
	Player_handler handler(player,map,send_queue,client);
	
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
	
	//std::chrono::duration<double> dur_prueba=std::chrono::system_clock::now();
	auto t1 = std::chrono::steady_clock::now();
    while (is_running) {
		t1=std::chrono::steady_clock::now();
		is_running=handler.handle();   //Capturo eventos del cliente y envio
		if(receivecontroller.update()){
			auto t2= std::chrono::steady_clock::now();
			std::chrono::duration<float, std::milli> diff;
			//std::chrono::duration<double> diff=t2-t1;
			diff = t2 - t1;
			//std::cout << "Delta es" << diff.count() << std::endl;
			if(diff.count()<100){
				int sleeping_time=(100-diff.count())*1000;
			//	std::cout << "SLeeping time es" << sleeping_time << std::endl;
				usleep(sleeping_time);
			}
		}   
	}
	//auto t2= std::chrono::steady_clock::now();
	//std::chrono::duration<double> diff=t2-t1;
	sender.stop();
	sender.join();
    receiver.stop();
	receiver.join();  
}

ClientManager::~ClientManager(){
    Mix_CloseAudio();
    SDL_Quit();
}