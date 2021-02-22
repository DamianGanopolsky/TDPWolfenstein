#ifndef __ELEMENT_PANEL_H__
#define __ELEMENT_PANEL_H__

#include <SDL2/SDL.h>

class Element_panel {
public:
	virtual ~Element_panel();

	virtual void copy_to_rederer(SDL_Renderer& renderer) = 0;
	bool operator<(Element_panel& other);
	static auto cmp() {
		return [] (Element_panel* el1, Element_panel* el2) {return *el1 < *el2;};
	}

protected: 
	float dist; 
};

#endif