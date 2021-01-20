#include "event.h"

Event::Event() {}
Event::~Event() {}
        
Event::Event(const Event& other) {}
Event& Event::operator=(const Event& other) {}

bool Event::send(const ConnectionId sender, const Socket& peer) {}