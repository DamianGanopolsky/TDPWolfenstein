#ifndef __ELEMENT_PANEL_STATUS_H__
#define __ELEMENT_PANEL_STATUS_H__

#include <map>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <string>


class Element_panel_status {
public:
	Element_panel_status(SDL_Renderer*& renderer, std::string root, int total_elem);
	Element_panel_status();
	Element_panel_status(Element_panel_status&& other);
	Element_panel_status& operator=(Element_panel_status&& other);
	~Element_panel_status();

	virtual void copy_to_rederer(int id);
	
protected:
	SDL_Renderer* renderer;
	std::map<int, SDL_Texture*> elements;
	int total_elem;  
};

#endif