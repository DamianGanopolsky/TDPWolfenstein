#include "Element_panel.h"

Element_panel::~Element_panel() {
}

bool Element_panel::operator<(Element_panel& other) {
	return this->dist < other.dist;
}
