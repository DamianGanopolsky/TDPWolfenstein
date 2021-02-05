#ifndef __CLIENT_SOCKET__
#define __CLIENT_SOCKET__

#include "../../Common/socket.h"
#include "../../Common/non_blocking_queue.h"
#include "UpdateMessage.h"

class ClientSocket {
public:
    ClientSocket(NonBlockingQueue<UpdateMessage*>& non_bloq_queue);
    int recv(char* recv_buff,int len);
    void send(uint8_t msg);
    

private:
    NonBlockingQueue<UpdateMessage*>& recv_queue;
    Socket socket;

};

#endif