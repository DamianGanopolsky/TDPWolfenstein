#ifndef __PANEL_WINDOW_H__
#define __PANEL_WINDOW_H__

#include <SDL2/SDL.h>
#include "Ray.h"
#include "Wall_texture.h"
#include "Ray_panel.h"
#include "Game_element.h"
#include "panel_status/Player_panel_status.h"
#include "Player_info.h"
#include <set>
#include <list>
#include "Map_2d.h"
#include "const.h"


class Panel_window {
public:
	Panel_window(Map_2d& MAP);
	Panel_window(const Panel_window& other) = delete;
	Panel_window(Panel_window&& other) = delete;
	~Panel_window();

	bool is_running();
	void update(std::set<Ray>&& rays, std::list<Game_element>&& elements, Player_info& player_info);

	void render_ending_screen();

private:
	Map_2d& map;
	SDL_Renderer* renderer;
	
	SDL_Window *window;
	bool running;
	Wall_texture wall_textures;
	Player_panel_status player_panel_status;
};

#endif