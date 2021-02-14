
#include "ClientManager.h"
#include "../Common/protocol.h"
#include "../Common/defs.h"
#include "../Common/exception.h"

int main(int argc,char* argv[]) {
	std::cout << "Argumentos:" << std::endl;
	for(int i=0;i<argc;i++){
		std::cout << "Argv es " << argv[i] << std::endl;
	}
	/*if(argc!=EXPECTED_ARGS_CLIENT){
		std::cerr << "Error invalid arguments!" << std::endl;
		return ERROR;
	}*/
	try{
		ClientManager clientmanager(argv[1],argv[2]);
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


