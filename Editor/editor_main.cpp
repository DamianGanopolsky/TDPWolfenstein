#include "EditorManager.h"
#include "../Common/defs.h"
#include "../Common/exception.h"



int main(int argc,char* argv[]){

    if(argc!=EXPECTED_ARGS_EDITOR){
		std::cerr << "Error invalid arguments!" << std::endl;
		return ERROR;
	}
    try{
        EditorManager editormanager;
        editormanager.start();
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