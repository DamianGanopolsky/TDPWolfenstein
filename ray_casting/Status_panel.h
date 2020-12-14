#ifndef __STATUS_PANEL_H__
#define __STATUS_PANEL_H__

#include <SDL2/SDL.h>

class Status_panel {
public:
	Status_panel();
	~Status_panel();

	void copy_to_rederer(SDL_Renderer& renderer);
};

#endif
