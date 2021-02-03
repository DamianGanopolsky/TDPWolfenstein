#include "Receiver.h"
#include <unistd.h>

void Receiver::stop(){
    receiving=false;
}


void Receiver::run(){
    while(receiving){
        //int bytes_received = 0; DESCOMENTAR
		//uint8_t buffer[2];  DESCOMENTAR
        
        std::cout << "Empiezo a recibir" << std::endl;
        sleep(20);
        //bytes_received=clientsocket->recv((char*)buffer,2);  DESCOMENTAR
        //UpdateMessage* updatemessage = new UpdateMessage(buffer[0],buffer[1]); DESCOMENTAR
        //std::cout << bytes_received << std::endl;
        /*switch(buffer[0]){
            case 0:
                uint8_t player_id;
                uint8_t pos_x;
                uint8_t pos_y;
                float angle;
                //uint8_t is_moving;
                //uint8_t is_shooting;
                updatemessage->load_movement_event(player_id,pos_x,pos_y,angle);

                break;
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
        }
*/

        //recv_queue.push(std::move(updatemessage));
    }
}