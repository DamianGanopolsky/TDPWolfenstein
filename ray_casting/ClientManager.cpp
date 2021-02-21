#include "ClientManager.h"
#include "../Common/blocking_queue.h"
#include "../Common/non_blocking_queue.h"
#include "ClientConnector/UpdateMessage.h"
#include "ClientConnector/Command.h"
#include "../Common/protocol.h"
#include "LoginView.h"
#include "LogInController.h"
#include <chrono>
#include <unistd.h>
#define PATH_TO_MAPS "../Maps/"
#define YAML_EXTENSION ".yaml"

ClientManager::ClientManager(std::string Host,std::string Port,std::string Nickname):\
host(Host),port(Port),nickname(Nickname){
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
	MusicSoundtrack music;
	music.play_editor();
	clientsock.send_nickname(nickname);
	New_Player_Event player_info=clientsock.recv_player();
	Player player(player_info);
	Map_2d map(player,PATH_TO_MAPS+player_info.map+YAML_EXTENSION);
	Panel_window panel;
	BlockingQueue<Command*> send_queue;
	panel.load_map_dimentions(map.get_height(),map.get_width(),map.map_get_players(),player_info.map);
	Client client(panel,player,map);
	Player_handler handler(player,map,send_queue,client);
	
	ReceiveController receivecontroller(player,map,recv_queue,client);
	Receiver receiver(&clientsock,recv_queue,receivecontroller);
	Sender sender(&clientsock,send_queue);
	receiver.start();
	sender.start();

	bool is_running=true;
	
	//std::chrono::duration<double> dur_prueba=std::chrono::system_clock::now();
	auto t1 = std::chrono::steady_clock::now();
	int it=0;
    while (is_running) {
		/*t1=std::chrono::steady_clock::now();
		is_running=handler.handle();   //Capturo eventos del cliente y envio
		if(!receivecontroller.update()){
			auto t2= std::chrono::steady_clock::now();
			std::chrono::duration<float, std::milli> diff;
			diff = t2 - t1;
			//std::cout << "Delta es" << diff.count() << std::endl;
			if(diff.count()<ClientConfig.constant_rate_loop_ms){
				int sleeping_time=(ClientConfig.constant_rate_loop_ms-diff.count())*1000;
				usleep(sleeping_time);
			}
		}*/
		/*
		else{
			auto t2= std::chrono::steady_clock::now();
			std::chrono::duration<float, std::milli> diff;
			diff = t2 - t1;
			if(diff.count()<5){
				int sleeping_time=(5-diff.count())*1000;
				usleep(sleeping_time);
			}
		}   
		*/
		t1=std::chrono::steady_clock::now();
		is_running=handler.handle();
		receivecontroller.update();
		if((it%101)==0){
			client.render();
		}
		auto t2= std::chrono::steady_clock::now();
		std::chrono::duration<float, std::milli> diff;
		diff = t2 - t1;
		if(diff.count()<16.67){
			int sleeping_time=(16.67-diff.count())*1000;
			usleep(sleeping_time);
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