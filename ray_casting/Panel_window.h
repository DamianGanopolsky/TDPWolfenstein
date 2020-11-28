#ifndef __PANEL_WINDOW_H__
#define __PANEL_WINDOW_H__

#include <SDL2/SDL.h>
#include "Ray.h"
#include <set>

class Panel_window {
public:
	Panel_window();
	Panel_window(const Panel_window& other) = delete;
	Panel_window(Panel_window&& other) = delete;
	~Panel_window();

	bool is_running();
	void update(std::set<Ray>&& rays);

private:
	SDL_Renderer* renderer;
	SDL_Texture * texture;
	SDL_Window *window;
	Uint32 *pixels;
	bool running; 	
};

#endif