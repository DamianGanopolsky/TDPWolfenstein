#ifndef __PANEL_WINDOW_H__
#define __PANEL_WINDOW_H__

#include <SDL2/SDL.h>
#include "Ray.h"
#include "Wall_texture.h"
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
	Wall_texture wall_textures;

	int get_number_tex(int point) const;
	void print_floor_and_ceiling(); 
	void to_render();
	void print_ray(Ray& ray); 
};

#endif