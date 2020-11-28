#ifndef __EVENT_HANDLER_H__
#define __EVENT_HANDLER_H__

#include "Player.h"

class Event_handler {
public:
	explicit Event_handler(Player& player);
	~Event_handler();

	void handle();
	bool is_running();

private:
	Player& player;
	bool running;	
};

#endif
