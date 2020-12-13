#include "Elements_panel_queue.h"
#include <iostream>

Elements_panel_queue::Elements_panel_queue() : q(Element_panel::cmp()) {
}

Elements_panel_queue::~Elements_panel_queue() {
	while(!this->q.empty()) {
		this->pop();
	}
}

void Elements_panel_queue::push(Game_element&& element) {
	this->q.push(std::move(new Game_element(std::move(element))));
}

void Elements_panel_queue::push(Ray_panel&& element) {
	this->q.push(std::move(new Ray_panel(std::move(element))));
}

Element_panel* Elements_panel_queue::top() {
	return this->q.top();
}

void Elements_panel_queue::pop() {
	Element_panel* element = q.top();
	if (element) {
		delete element; 
	}
	this->q.pop();	
}

bool Elements_panel_queue::empty() {
	return this->q.empty();
}
