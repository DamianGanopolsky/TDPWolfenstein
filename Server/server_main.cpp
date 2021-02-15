#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include "./server.h"
#include "../Common/exception.h"
#include "../Server/Model/constants/YamlConfig.h"

int main(int argc, char* argv[]) {
	if (argc != 3) {
		std::cerr << "Error invalid arguments" <<std::endl;
		return 1;
	}
	char* service = argv[1];
	try {
		Server server(service,argv[2]);
		server();
	} catch (const Exception& e) {
		std::cerr << e.what() << std::endl;
		return 3;
	} catch (...) {
		std::cerr << "Unknown error" << "\n";
		return 4;
	}
	return 0;
}
