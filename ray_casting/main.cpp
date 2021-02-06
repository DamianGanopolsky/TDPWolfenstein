
#include "ClientManager.h"
#include "../Common/protocol.h"
#include "../Common/defs.h"

int main(int argc,char* argv[]) {
	//START_MOVING_UP_CMD 
	if(argc!=EXPECTED_ARGS_CLIENT){
		std::cerr << "Error invalid arguments!" << std::endl;
		return ERROR;
	}
	ClientManager clientmanager;
	
	clientmanager.start();

	return SUCCESS;
}


