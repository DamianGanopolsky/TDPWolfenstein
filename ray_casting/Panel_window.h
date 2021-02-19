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
	Panel_window();
	Panel_window(const Panel_window& other) = delete;
	Panel_window(Panel_window&& other) = delete;
	~Panel_window();
	bool is_running();
	void update(std::set<Ray>&& rays, std::list<Game_element>&& elements, Player_info& player_info);
	void render_player_lost_screen();
	void render_ending_screen();
	void render_waiting_screen();
	void load_map_dimentions(int MAP_HEIGHT,int MAP_WIDTH);

	void render_login_screen();

private:
	SDL_Renderer* renderer;

	
	SDL_Window *window;
	SDL_Texture* Ending_screen_base;
	SDL_Texture* waiting_screen;
	bool running;
	Wall_texture wall_textures;
	Player_panel_status player_panel_status;
	int map_width;
	int map_height;

};

#endif