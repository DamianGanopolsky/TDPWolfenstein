#ifndef __FACE_PANEL_STATUS_H__
#define __FACE_PANEL_STATUS_H__

#include <map>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>


class Face_panel_status {
public:
	explicit Face_panel_status(SDL_Renderer*& renderer);
	Face_panel_status();
	Face_panel_status(Face_panel_status&& other);
	Face_panel_status& operator=(Face_panel_status&& other);
	~Face_panel_status();

	void copy_to_rederer(int health);
	
private:
	SDL_Renderer* renderer;
	std::map<int, SDL_Texture*> faces; 
};

#endif