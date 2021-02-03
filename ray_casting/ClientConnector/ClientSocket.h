#ifndef __CLIENT_SOCKET__
#define __CLIENT_SOCKET__

#include "../../Common/socket.h"

class ClientSocket {
public:
    ClientSocket();
    int recv(char* recv_buff,int len);
    void send(uint8_t msg);
    

private:
    Socket socket;

};

#endif