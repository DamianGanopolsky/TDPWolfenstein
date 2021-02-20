#ifndef __CLIENT_SOCKET__
#define __CLIENT_SOCKET__

#include "../../Common/socket.h"
#include "../../Common/non_blocking_queue.h"
#include "UpdateMessage.h"
#include "../const.h"

class ClientSocket {
public:
    ClientSocket(NonBlockingQueue<UpdateMessage*>& non_bloq_queue,const char* Host,const char* Port);
    void recv(char* recv_buff,int len);
    void send(uint8_t msg);
    void close();

    New_Player_Event recv_player();

    New_Player_Event recv_player_func();

    void send_nickname(std::string Nickname);

    

private:
    NonBlockingQueue<UpdateMessage*>& recv_queue;
    Socket socket;
    New_Player_Event my_player;
    std::vector<Player_stats> final_stats;
    int initial_lives;

};

#endif