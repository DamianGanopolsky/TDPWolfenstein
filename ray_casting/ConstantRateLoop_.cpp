#include "ConstantRateLoop_.h"
#include <iostream>
#include <cmath>
#include <chrono>
#include <unistd.h>


ConstantRateLoop_::ConstantRateLoop_(Player_handler& Player_Handler,Client& Client,\
        ReceiveController& Receive_Controller):is_running(true),rate(1000/30),\
        player_handler(Player_Handler),client(Client),receive_controller(Receive_Controller){

}

void ConstantRateLoop_::run(){
    auto t1 = std::chrono::steady_clock::now();
    auto t2 = t1;
    std::chrono::duration<float, std::milli> diff;
    int rest = 0, behind = 0, lost = 0;
    int it = 1;
    client.render();

    while (is_running) {
       // _newConnections();
        //_newCommands();
        //game.updatePlayers(it);
        //_finishedConnections();
        std::cout << "Capturo eventos del cliente y envio" << std::endl;
		//client.render();
        is_running=player_handler.handle(); //Capturo eventos del cliente y envio
        std::cout << "Recibo eventos del server, updateo y dibujo" << std::endl;
		receive_controller.update();    //Recibo eventos y actualizo
        client.render();
        //client.render();
        //HANDLER
        //UPDATE Va a tener el hilo recv adentro
        //DIBUJAR
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
        std::cout << "Rest es" << rest << std::endl;
        sleep(rest/1000);
        //std::sleep_for(std::chrono::milliseconds(rest));
        t1 += std::chrono::milliseconds(rate);
        it += 1;
    }
    std::cout <<"Loop: termino el loop"<< std::endl;
    //clients_connected.stop();
    //_deleteQueues();
    std::cout <<"Loop: termino "<< std::endl;

}