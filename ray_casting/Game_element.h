#ifndef __GAME_ELEMENT_H__
#define __GAME_ELEMENT_H__

#include "Player.h"
#include "const.h"
#include "Element_panel.h"
#include <SDL2/SDL.h>
#include <string>


class Game_element : public Element_panel {
public:
	Game_element(int pos_x, int pos_y, std::string img_path, Player& player);
	Game_element(Game_element&& other);
	~Game_element();

	bool is_visible();  
	virtual void copy_to_rederer(SDL_Renderer& renderer) override; 

private:
	int pos_ray;
	std::string img_path;
};

#endif