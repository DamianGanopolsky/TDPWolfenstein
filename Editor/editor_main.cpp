#include "EditorManager.h"
#include "../Common/defs.h"



int main(int argc,char* argv[]){

    if(argc!=EXPECTED_ARGS_EDITOR){
		std::cerr << "Error invalid arguments!" << std::endl;
		return ERROR;
	}
    EditorManager editormanager;
    editormanager.start();
    return SUCCESS;
}