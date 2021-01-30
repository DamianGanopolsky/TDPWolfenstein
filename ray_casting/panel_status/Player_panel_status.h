#ifndef __STATUS_PANEL_H__
#define __STATUS_PANEL_H__

#include <SDL2/SDL.h>
#include "../Player_info.h"
#include <SDL2/SDL.h>
#include "Element_panel_status.h"
#include "../SdlClasses/SdlText.h"

class Player_panel_status {
public:
	explicit Player_panel_status(SDL_Renderer*& renderer);
	Player_panel_status();
	Player_panel_status(Player_panel_status&& other);
	Player_panel_status& operator=(Player_panel_status&& other);
	~Player_panel_status();

	void copy_to_rederer(Player_info& player_info);
	SDL_Texture* get_texture(int value, int id);

private:
	SDL_Renderer* renderer;
	SDL_Texture* status_tex;
	Element_panel_status face_status;
	Element_panel_status weapon_status;
	Element_panel_status number_status;
	Element_panel_status guardia_status;
	Element_panel_status knife_status;
	Element_panel_status pistola_status;
	Element_panel_status automaticgun_status;
	Element_panel_status chaincannon_status;
	Element_panel_status elite_guard_status;
	Element_panel_status official_guard_status;
	Element_panel_status bullets;
	Element_panel_status food;
	Element_panel_status medical_kit;
	Element_panel_status key;
	Element_panel_status automatic_gun;
	Element_panel_status treasure;
	Element_panel_status chain_cannon;
	//SdlText numero;
	
	
	
	

	void copy_to_rederer_weapon(Player_info& info);
	void copy_to_rederer_face(int health);
	void copy_to_rederer_lives(int lives);
	void copy_to_rederer_score(int score);
	void copy_to_rederer_health(int health);
	void copy_to_rederer_ammo(int health);
	void copy_to_rederer_level(int level);
	void copy_to_rederer_number(int number, int digits, SDL_Rect& SrcR, bool is_cero);
};

#endif
