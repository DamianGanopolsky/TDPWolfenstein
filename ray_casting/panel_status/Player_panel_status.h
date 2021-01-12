#ifndef __STATUS_PANEL_H__
#define __STATUS_PANEL_H__

#include <SDL2/SDL.h>
#include "../Player_info.h"
#include <SDL2/SDL.h>
#include "Face_panel_status.h"

class Player_panel_status {
public:
	explicit Player_panel_status(SDL_Renderer*& renderer);
	Player_panel_status();
	Player_panel_status(Player_panel_status&& other);
	Player_panel_status& operator=(Player_panel_status&& other);
	~Player_panel_status();

	void copy_to_rederer(Player_info& player_info);

private:
	SDL_Renderer* renderer;
	SDL_Texture* status_tex;
	Face_panel_status face_status;
};

#endif
