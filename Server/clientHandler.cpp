#include "./clientHandler.h"
//-------------------------------------------------------------------------------
ClientHandler::ClientHandler(Socket& socket, const ConnectionId id, 
						NonBlockingQueue<ConnectionId*>& finished_connections) : 
						peer(std::move(socket)),
						finished_connections(finished_connections),
						id(id), 
						dead_threads(0) {}

ClientHandler::~ClientHandler() {
	/*notifications.close(); 
    Notification* notification = NULL;
    while ((notification = notifications.pop())) {
        delete notification;
    }*/
}

void ClientHandler::_deadThread() {
	std::unique_lock<std::mutex> l(m);
    if ((++dead_threads) == 2) {
        finished_connections.push(new ConnectionId(id));
    }
}

void ClientHandler::_send() {
	/*
	try {
        Notification* notification = nullptr;
        bool socket_valid = true;
        while ((notification = notifications.pop())) {
            if (!notification->isForEveryMap()) {
                if (!(notification->getMapId() == this->map)) {
                    if (notification->isEntityBroadcast()) {
                        if (notification->getSourceInstanceId() != this->id) {
                            delete notification;
                            continue;
                        }
                    } else {
                        delete notification;
                        continue;
                    }
                }
            }
            socket_valid = notification->send(this->id, peer);
            delete notification;

            if (!socket_valid) {
                break;
            }
        }
    } catch (const std::exception& e) {
        stop();
        std::cerr << "Error in ClientHandler::_send(): "<< e.what() 
														<< std::endl;
    } catch (...) {
        stop();
        std::cerr << "Unknown error ClientHandler::_send(). "<< std::endl;;
    }
    _deadThread();
	*/
}

void ClientHandler::_receive() {
	/*
	try {
        uint8_t opcode;
        while (peer >> opcode) {
            if(opcode == COMMAND_OPCODE) {
				uint8_t opcode_cmd;
				peer >> opcode_cmd;
				try {
					Command* cmd = CommandFactory::newCommand(id, opcode_cmd, peer);
					commands.push(cmd);
				} catch (const UnknownCommandException& e) {
					// Comando desconocido. Envio error.
					Reply* reply_error = new Reply(ERROR_MSG, e.what());
					this->notifications.push(reply_error);
				}
			} else {
				throw Exception("Unknown opcode received by client handler.");
			}
			
        }
    } catch (const std::exception& e) {
        stop();
        std::cerr << "Error in ClientHandler::_receive(): "<< e.what() 
														<< std::endl;
    } catch (...) {
        stop();
        std::cerr << "Unknown error ClientHandler::_receive(). "<< std::endl;;
    }

    this->notifications.close();
    _deadThread();
	*/
}

void ClientHandler::start() {
	send = std::thread(&ClientHandler::_send, this);
    receive = std::thread(&ClientHandler::_receive, this);
}

//void ClientHandler::push(Notification* notification) {}

//void ClientHandler::changeMap(Id map) {}

void ClientHandler::joinThreads() {
	if (send.joinable()) {
        send.join();
    }
    if (receive.joinable()) {
        receive.join();
    }
	try {
        peer.shutdown();
		peer.close();
    } catch (const Exception& e) {
        std::cerr << "Error while shutingdown peer: "<< e.what() 
														<< std::endl;
    }
}

void ClientHandler::stop() {
	//notifications.close();
	try{
		peer.shutdown();
		peer.close();
	} catch (const Exception& e) {
		std::cerr << "Error while shutingdown peer: "<< e.what() 
														<< std::endl;
	}
}


