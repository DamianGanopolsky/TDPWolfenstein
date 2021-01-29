#include "./clientHandler.h"
//-------------------------------------------------------------------------------
ClientHandler::ClientHandler(Socket& socket, const ConnectionId id, 
						NonBlockingQueue<ConnectionId*>& finished_connections,
                        NonBlockingQueue<Command*>& commands) : 
						peer(std::move(socket)),
						finished_connections(finished_connections),
                        commands(commands), id(id), 
						dead_threads(0) {}

ClientHandler::~ClientHandler() {
	notifications.close(); 
    Notification* notification = NULL;
    while ((notification = notifications.pop())) {
        delete notification;
    }
}

void ClientHandler::_deadThread() {
	std::unique_lock<std::mutex> l(m);
    if ((++dead_threads) == 2) {
        finished_connections.push(new ConnectionId(id));
    }
}

void ClientHandler::_send() {
	try {
        Notification* notification = nullptr;
        bool socket_valid = true;
        while ((notification = notifications.pop())) {
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
        std::cerr << "Unknown error ClientHandler::_send(). "<< std::endl;
    }
    _deadThread();
}

void ClientHandler::_receive() {
	try {
        int bytes_received = 0;
		uint8_t buffer[2];
        while (peer.receive(buffer, 2, bytes_received)) {
            uint8_t opcode = buffer[0];
            uint8_t command_opcode = buffer[1];
            if (opcode == COMMAND_OPCODE) {
				try {
					Command* cmd = Command::newCommand(id, command_opcode, peer);
					commands.push(cmd);
				} catch (const std::exception& e) {
					Message* msg_error = new Message(ERROR_MSSG, e.what());
					this->notifications.push(msg_error);
				}
			} else {
				throw Exception("Unknown opcode received.");
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
}

void ClientHandler::run() {
    while(is_running) {
        send = std::thread(&ClientHandler::_send, this);
        receive = std::thread(&ClientHandler::_receive, this);
    }
}

bool ClientHandler::isRunning() const{
    return this->is_running;
}
void ClientHandler::push(Notification* notification) {
    notifications.push(notification);
}

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
    is_running = false;
	notifications.close();
	try{
		peer.shutdown();
		peer.close();
	} catch (const Exception& e) {
		std::cerr << "Error while shutingdown peer: "<< e.what() 
														<< std::endl;
	}
}


