#ifndef __PANEL_WINDOW_H__
#define __PANEL_WINDOW_H__

#include <SDL2/SDL.h>

class Panel_window {
public:
	Panel_window();
	Panel_window(const Panel_window& other) = delete;
	Panel_window(Panel_window&& other) = delete;
	~Panel_window();

	bool is_running();
	void update();

private:
	SDL_Renderer* renderer;
	SDL_Texture * texture
	SDL_Window *window;
	Uint32 *pixels;
	bool running; 	
};

#endif