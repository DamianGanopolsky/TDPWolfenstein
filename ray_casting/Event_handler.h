#ifndef __EVENT_HANDLER_H__
#define __EVENT_HANDLER_H__

#include "Player.h"
#include <thread>

class Event_handler {
public:
	Event_handler();
	~Event_handler();

	void handle(Player& player);
	bool is_running();

private:
	// Es necesario protegerlos de race condition?
	bool running;
	std::thread handler_thread; 	
};

#endif
