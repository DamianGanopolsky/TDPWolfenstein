#include "Element_panel_status.h"
#include "../const.h"

Element_panel_status::Element_panel_status(SDL_Renderer*& renderer, std::string root, int total_elem) :
									renderer(renderer) {
	for (int i = 0; i < total_elem; i++) {
		std::string new_root = root;
		new_root.append(std::to_string(i));
		new_root.append(".png");
		SDL_Surface *status_img = IMG_Load(new_root.c_str());
		this->elements[i] = SDL_CreateTextureFromSurface(this->renderer, status_img);
		SDL_FreeSurface(status_img);
	}
}

Element_panel_status::Element_panel_status(Element_panel_status&& other) : 
											renderer(other.renderer) {
	for (auto it = other.elements.begin(); it != other.elements.end(); ++it) {
		this->elements[it->first] = other.elements[it->first];
		other.elements[it->first] = nullptr;
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

	for (auto it = other.elements.begin(); it != other.elements.end(); ++it) {
		this->elements[it->first] = other.elements[it->first];
		other.elements[it->first] = nullptr;
	}

	return *this;	
}

Element_panel_status::Element_panel_status() {	
}

Element_panel_status::~Element_panel_status() {
	for (auto it = this->elements.begin(); it != this->elements.end(); ++it) {
		if (it->second) {
			SDL_DestroyTexture(it->second);
		}
	}
}

void Element_panel_status::copy_to_rederer(int id, SDL_Rect *SrcR) {
    SDL_RenderCopy(this->renderer, this->elements[id], NULL, SrcR);
}

