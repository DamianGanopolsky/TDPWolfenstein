#include "ClientManager.h"

ClientManager::ClientManager(){
	if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,1024)<0){
        std::cout << "eRROR:" << Mix_GetError() << std::endl;
    }

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cout << "ERROR init video" << std::endl;
	}
    TTF_Init();
}


void ClientManager::start(){
	ClientSocket clientsock;
	Receiver receiver(&clientsock);
	Sender sender(&clientsock);
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
	//sender.join();
    receiver.stop();
	//receiver.join();  
}

ClientManager::~ClientManager(){
    Mix_CloseAudio();
    SDL_Quit();
}