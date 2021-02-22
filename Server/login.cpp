#include "./login.h"

#include <iostream>
#include <cstring>

Login::Login(Socket& peer, NonBlockingQueue<ConnectionElement*>& new_connections)
    : is_running(false),
      peer(std::move(peer)),
      new_connections(new_connections) {}

Login::~Login() {}

std::string Login::_receive() {
    std::cout << "Login: _receive"<<std::endl;
    bool connected = false;
    std::string nickname = " ";
    int bytes_received = 0;
    uint32_t name_size[1];
    while (!connected) {
        nickname.clear();
        nickname.shrink_to_fit();
        if (!(peer.receive((char*)name_size, sizeof(name_size), bytes_received))) {
            throw Exception("Error socket closed before expected.");
        }
        name_size[0] = le32toh(name_size[0]);
        int name_size_ = int (name_size[0]);
        std::cout << "Name size es" << name_size_ << std::endl;
        nickname.reserve(name_size_);
        char name[name_size_];
        if (!(peer.receive(name, name_size_, bytes_received))) {
            throw Exception("Error socket closed before expected.");
        }
        for (int i = 0; i<name_size_; i++) {
            nickname += name[i];
        }
        connected = true;
    }
    return nickname;
}

void Login::run() {
    is_running = true;
    std::cout << "Login: run()"<<std::endl;
    try {
        std::string nickname = _receive();
        new_connections.push(new ConnectionElement(peer, nickname));
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
