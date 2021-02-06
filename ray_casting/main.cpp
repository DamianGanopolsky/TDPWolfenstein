
#include "ClientManager.h"
#include "../Common/protocol.h"
#include "../Common/defs.h"
#include "../Common/exception.h"

int main(int argc,char* argv[]) {
	if(argc!=EXPECTED_ARGS_CLIENT){
		std::cerr << "Error invalid arguments!" << std::endl;
		return ERROR;
	}
	try{
		ClientManager clientmanager;
		clientmanager.start();
	}
	catch(const Exception& e){
		std::cerr << e.what() << std::endl;
		return 2;
	}
	catch(...){
		std::cerr << "Unknown error" << std::endl;
		return 3;
	}
	return SUCCESS;
}


