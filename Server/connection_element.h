#ifndef CONNECTION_ELEMENT_H
#define CONNECTION_ELEMENT_H

#include "../Common/socket.h"

struct ConnectionElement{
    Socket peer;
    std::string nickname;
    ConnectionElement(Socket& peer, std::string& nickname) : 
                peer(std::move(peer)), nickname(nickname) {}
};


#endif