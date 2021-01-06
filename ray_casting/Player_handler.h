#ifndef __PLAYER_HANDLER_H__
#define __PLAYER_HANDLER_H__

#include "Player.h"
#include <thread>

class Player_handler {
public:
	Player_handler(Player& player, bool& running);
	Player_handler(Player_handler&& other);
	~Player_handler();

	void handle();

private:
	// Es necesario protegerlos de race condition?
	Player& player;
	bool& running;
};

#endif
