#include "Event_handler.h"
#include "Player_handler.h"
#include <SDL2/SDL.h>
#include <utility>

Event_handler::Event_handler() : running(true) {
}
Event_handler::~Event_handler() {
    if (this->handler_thread.joinable()) {
        this->handler_thread.join();
    }
}

void Event_handler::handle(Player& player) {
    Player_handler player_handler(player, this->running);
    std::thread player_thread(&Player_handler::handle, std::move(player_handler));
    this->handler_thread = std::move(player_thread);
}

bool Event_handler::is_running() {
	return this->running;
}