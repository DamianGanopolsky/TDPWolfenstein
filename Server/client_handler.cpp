#include "./client_handler.h"

ClientHandler::ClientHandler(Socket& socket, const ConnectionId id, 
						NonBlockingQueue<ConnectionId*>& finished_connections,
                        NonBlockingQueue<Command*>& commands) : 
						peer(std::move(socket)), is_running(false), id(id),
						finished_connections(finished_connections),
                        dead_threads(0), commands(commands) {}

ClientHandler::~ClientHandler() {
	notifications.close(); 
}

void ClientHandler::_deadThread() {
	std::unique_lock<std::mutex> l(m);
    if ((++dead_threads) == 2) {
        finished_connections.push(new ConnectionId(id));
    }
}

void ClientHandler::_send() {
	try {
        std::shared_ptr<Notification> notification = nullptr;
        bool is_sent = true;
        while ((notification = notifications.pop())) {
            is_sent = notification->send(this->id, this->peer);
            if (!is_sent) {
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
        while (peer.receive((char *)buffer, 2, bytes_received)) {
            uint8_t opcode = buffer[0];
            uint8_t command_opcode = buffer[1];
            if (opcode == COMMAND_OPCODE) {
				try {
					Command* cmd = Command::newCommand(id, command_opcode, peer);
					commands.push(cmd);
				} catch (const std::exception& e) {
                    std::cout<<"Unkown command."<<std::endl;
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
    is_running =true;
    send = std::thread(&ClientHandler::_send, this);
    receive = std::thread(&ClientHandler::_receive, this);
}

bool ClientHandler::isRunning() const{
    return this->is_running;
}
void ClientHandler::push(std::shared_ptr<Notification>& notification_ptr) {
    notifications.push(notification_ptr);
}

void ClientHandler::joinThreads() {
	if (send.joinable()) {
        send.join();
    }
    if (receive.joinable()) {
        receive.join();
    }
	try {
        peer.shutdown();
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


