#ifndef __GAME_ELEMENT_H__
#define __GAME_ELEMENT_H__

#include "Player.h"
#include "const.h"
#include "Element_panel.h"
#include <SDL2/SDL.h>
#include <string>




class Game_element : public Element_panel {
public:
	Game_element(int pos_x, int pos_y, int type_id, int vision_angle, Player& player);
	Game_element(Game_element&& other);
	~Game_element();

	//Game_element& operator=(const Game_element& other);

	bool is_visible();
	void set_texture(SDL_Texture* tex);  
	int get_texture_section();
	int get_type_id();
	void update(int pos_x, int pos_y, int type_id, int vision_angle, Player& player);
	virtual void copy_to_rederer(SDL_Renderer& renderer) override; 

private:
	int pos_ray;
	int type_id;
	int texture_section;
	
	SDL_Texture* texture;
	int angle_;

	int get_texture_section(int element_angle, int player_angle);
	int get_angle_section(int angle);
};

#endif