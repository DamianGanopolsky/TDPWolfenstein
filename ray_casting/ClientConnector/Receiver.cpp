#include "Receiver.h"
#include <unistd.h>

void Receiver::stop(){
    receiving=false;
}


void Receiver::run(){
    //uint8_t buffer[2];
    //New_Player_Event my_player=clientsocket->recv_player((char*)buffer);
    //recv_controller.InitializeClient(my_player);
    while(receiving){
        //int bytes_received = 0; //DESCOMENTAR
		uint8_t buffer[2];  //DESCOMENTAR
        
        //std::cout << "Empiezo a recibir" << std::endl;
        //sleep(20);
        clientsocket->recv((char*)buffer,2);  //DESCOMENTAR
        //std::cout << bytes_received << std::endl;
       // std::cout << "Recibi" << bytes_received << std::endl;
        //UpdateMessage* updatemessage = new UpdateMessage(buffer[0],buffer[1]); //DESCOMENTAR
        //std::cout << bytes_received << std::endl;
        /*switch(buffer[0]){
            case 0:
                uint8_t player_id;
                clientsocket->recv((char*)player_id,1);
                uint8_t pos_x;
                clientsocket->recv((char*)pos_x,1);
                uint8_t pos_y;
                clientsocket->recv((char*)pos_y,1);
                float angle; 
                clientsocket->recv((char*)angle,1); // Aca va a haber un temita
                //uint8_t is_moving;
                clientsocket->recv((char*)is_moving,1);
                //uint8_t is_shooting;
                clientsocket->recv((char*)is_shooting,1);
                updatemessage->load_movement_event(player_id,pos_x,pos_y,angle,is_moving,is_shooting);

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