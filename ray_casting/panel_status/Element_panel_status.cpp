#include "Element_panel_status.h"
#include "../const.h"

Element_panel_status::Element_panel_status(SDL_Renderer*& renderer, std::string root, int total_elem) :
									renderer(renderer), total_elem(total_elem) {
	for (int i = 0; i <= total_elem; i++) {
		std::string new_root = root;
		new_root.append(std::to_string(i));
		new_root.append(".png");
		SDL_Surface *status_img = IMG_Load(new_root.c_str());
		this->elements[i] = SDL_CreateTextureFromSurface(this->renderer, status_img);
		SDL_FreeSurface(status_img);
	}
}

Element_panel_status::Element_panel_status(Element_panel_status&& other) : 
											renderer(other.renderer), total_elem(other.total_elem) {
	for (int i = 1; i <= this->total_elem; i++) {
		this->elements[i] = other.elements[i];
		other.elements[i] = nullptr;
	}

}

Element_panel_status& Element_panel_status::operator=(Element_panel_status&& other) {
	if (this == &other) {
		return *this;
	}

	for (auto it = this->elements.begin(); it != this->elements.end(); ++it) {
		if (it->second) {
			SDL_DestroyTexture(it->second);
		}
	}	

	this->renderer = other.renderer;
	this->total_elem = other.total_elem;

	for (auto it = other.elements.begin(); it != other.elements.end(); ++it) {
		this->elements[it->first] = other.elements[it->first];
		other.elements[it->first] = nullptr;
	}

	return *this;	
}

Element_panel_status::Element_panel_status() {	
}

Element_panel_status::~Element_panel_status() {
	for (int i = 1; i <= this->total_elem; i++) {
		if (this->elements[i]) {
			SDL_DestroyTexture(this->elements[i]);
		}
	}
}

void Element_panel_status::copy_to_rederer(int health) {

}

