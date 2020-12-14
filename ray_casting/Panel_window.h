#ifndef __PANEL_WINDOW_H__
#define __PANEL_WINDOW_H__

#include <SDL2/SDL.h>
#include "Ray.h"
#include "Wall_texture.h"
#include "Ray_panel.h"
#include "Game_element.h"
#include "Status_panel.h"
#include <set>
#include <list>
#include "const.h"


class Panel_window {
public:
	Panel_window();
	Panel_window(const Panel_window& other) = delete;
	Panel_window(Panel_window&& other) = delete;
	~Panel_window();

	bool is_running();
	void update(std::set<Ray>&& rays, std::list<Game_element>&& elements);

private:
	SDL_Renderer* renderer;
	SDL_Window *window;
	bool running;
	Wall_texture wall_textures;
	Status_panel status_panel;
};

#endif