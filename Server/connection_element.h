#ifndef CONNECTION_ELEMENT_H
#define CONNECTION_ELEMENT_H

#include "../Common/socket.h"

struct ConnectionElement{
    Socket peer;
    ConnectionElement(Socket& peer) : peer(std::move(peer)){}
};


#endif