#ifndef __CLIENT_SOCKET__
#define __CLIENT_SOCKET__

#include "../../Common/socket.h"

class ClientSocket {
public:
    ClientSocket();
    int recv();
    void send(int msg);
    

private:
    //Socket socket;
    int asd;

};

#endif