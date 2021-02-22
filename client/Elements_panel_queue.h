#ifndef __ELEMENTS_PANEL_QUEUE_H__
#define __ELEMENTS_PANEL_QUEUE_H__

#include "Element_panel.h"
#include "Ray_panel.h"
#include "Game_element.h"
#include <queue>

class Elements_panel_queue {
public:
	Elements_panel_queue();
	~Elements_panel_queue();

	void push(Game_element&& element); 
	void push(Ray_panel&& element);
	Element_panel* top();
	void pop();
	bool empty();

private:
	std::priority_queue<Element_panel*, 
						std::vector<Element_panel*>, 
						decltype(Element_panel::cmp())> q;	
	
};

#endif
