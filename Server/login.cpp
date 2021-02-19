#include "./login.h"

#include <iostream>

Login::Login(Socket& peer, NonBlockingQueue<ConnectionElement*>& new_connections)
    : is_running(false),
      peer(std::move(peer)),
      new_connections(new_connections) {
          std::cout << "Login: constructor"<<std::endl;
      }

Login::~Login() {}

std::string Login::_receive() {
    std::cout << "Login: _receive"<<std::endl;
    bool connected = false;
    //uint8_t opcode;
    std::string nickname;
    int bytes_received = 0;
    uint32_t name_size[1];
    while (!connected) {
        std::cout << "Login: entra en while"<<std::endl;
        peer.receive((char*)name_size, sizeof(name_size), bytes_received);
        /*if (!(peer.receive((char*)name_size, sizeof(name_size), bytes_received))) {
            throw Exception("Error socket closed before expected.");
        }*/
        std::cout << "Login: 1er recieve"<<std::endl;
        name_size[0] = le32toh(name_size[0]);
        int name_size_ = int (name_size[0]);
        std::cout << "Name size es" << name_size_ << std::endl;
        char name[name_size_];
        peer.receive(name, name_size_, bytes_received);
        /*if (!(peer.receive(name, name_size_, bytes_received))) {
            throw Exception("Error socket closed before expected.");
        }*/
        std::cout << "Login: 2do recieve"<<std::endl;
        std::string name__(name);
        nickname = name__.substr(0,name_size_);
        std::cout << "Name es" << nickname << std::endl;
        //if (!(peer.receive((char *)buffer, 1, bytes_received))) {
            //throw Exception("Error socket closed before expected.");
        //}
    }
    return nickname;
    //return "";
}

void Login::run() {
    is_running = true;
    std::cout << "Login: run()"<<std::endl;
    try {
        std::cout << "Login: start receive"<<std::endl;
        std::string nickname = _receive();
        std::cout << "Login: received"<<std::endl;
        new_connections.push(new ConnectionElement(peer, nickname));
        std::cout << "Login: push new connection"<<std::endl;
    } catch (const std::exception& e) {
        try {
            peer.shutdown();
        } catch (const Exception& e) {
            std::cout << "Error while shutting down peer in login."<<std::endl;
        }
        peer.close();
    } catch (...) {
        try {
            peer.shutdown();
        } catch (const Exception& e) {
            std::cout << "Unknown error."<<std::endl;
        }
        peer.close();
    }
    is_running = false;
}

bool Login::isRunning() const {
    return is_running;
}

void Login::stop() {
    if (is_running) {
        try {
            peer.shutdown();
        } catch (const Exception& e) {
            std::cout<<"Error while shutting down peer in login."<<std::endl;
        }
        peer.close();
    }
}
