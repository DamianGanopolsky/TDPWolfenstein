#ifndef __CLIENT_SOCKET__
#define __CLIENT_SOCKET__

#include "../../Common/socket.h"

class ClientSocket {
public:
    ClientSocket();
    int recv();
    void send(uint8_t msg);
    

private:
    Socket socket;

};

#endif