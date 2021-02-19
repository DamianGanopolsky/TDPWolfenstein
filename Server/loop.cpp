#include "loop.h"
#include <chrono>

Loop::Loop(NonBlockingQueue<ConnectionElement*>& new_connections,std::string mapYaml) : 
                map(12), rate(1000/30), 
                pre_game(clients_connected, mapYaml, rate), 
                clients_connected(commands, finished_connections),
                commands(), 
                finished_connections(), 
                new_connections(new_connections),
                is_running(true), has_players(false),
                first_game_it(0) {}

Loop::~Loop() {}

void Loop::_newConnections() {
    ConnectionElement* connection = nullptr;
    while ((connection = this->new_connections.pop())) {
        std::cout <<"Loop: new_connection"<< std::endl;
        //ConnectionId id = this->game.newPlayer();
        ConnectionId id = pre_game.addPlayer(connection->nickname);
        std::cout <<"Loop: new player added"<< id <<std::endl;
        if (id) {
            std::cout <<"Loop: notifico new players"<< id <<std::endl;
            clients_connected.add(id, connection->peer);
            pre_game.notifyNewPlayer(id);
        } else {
            //NOTIFICAR AL CLIENTE QUE LA PARTIDA ESTA LLENA
        }
        delete connection;
    } 
}

void Loop::_newCommands() {
    Command* command = nullptr;
    while((command = this->commands.pop())) {
        std::cout <<"Loop: new_command"<< std::endl;
        try {
            //command->run(this->game);
            command->run(pre_game.game);
        } catch (const std::exception& e) {
            Notification* message = new Message(ERROR_MSSG, e.what());
            clients_connected.sendMessageToAll(message);
        }
        delete command;
    }
}

void Loop::_finishedConnections() {
    ConnectionId* connection = nullptr;
    while ((connection = finished_connections.pop())){
        std::cout <<"Loop: deleting finished connection"<< std::endl;
        //game.deletePlayer(*connection);
        pre_game.deletePlayer(*connection);
        clients_connected.remove(*connection);
        delete connection;
    }
}

void Loop::_deleteQueues() {
    Command* command = nullptr;
    while((command = this->commands.pop())) {
        delete command;
    }
    ConnectionId* connection = nullptr;
    while ((connection = finished_connections.pop())){
        //game.deletePlayer(*connection);
         pre_game.deletePlayer(*connection);
        delete connection;
    }
}

void Loop::run() {
    std::cout <<"Loop: comenzo el loop"<< std::endl;
    auto t1 = std::chrono::steady_clock::now();
    auto t2 = t1;
    std::chrono::duration<float, std::milli> diff;
    int rest = 0, behind = 0, lost = 0;
    int it = 1;
    while (is_running) {
        _newConnections();
        _newCommands();
        //std::cout <<"Loop: update game"<< std::endl;
        //this->has_players = game.updatePlayers(it);
        bool start_game = pre_game.update(it);
        if ((start_game) && (first_game_it == 0)) { //SOLO TIENE QUE ENRTAR UNA SOLA VEZ
            std::cout <<"Loop: started game"<<std::endl;
            Notification* notification = new Event(START_EV);
            clients_connected.sendEventToAll(notification);
            ++first_game_it;
        }
        _finishedConnections();
        
        it = 0;
        t2 = std::chrono::steady_clock::now();
        diff = t2 - t1;
        rest = rate - std::ceil(diff.count());

        if (rest < 0) {
            behind = -rest;
            lost = rate + (behind - behind % rate);
            rest = rate - behind % rate;
            t1 += std::chrono::milliseconds(lost);
            it += std::floor(lost / rate);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(rest));
        t1 += std::chrono::milliseconds(rate);
        it += 1;
    }
    std::cout <<"Loop: termino el loop"<< std::endl;
    clients_connected.stop();
    _deleteQueues();
    std::cout <<"Loop: termino "<< std::endl;
}

void Loop::stop() {
    this->is_running = false;
}