#ifndef __RAY_PANEL_H__
#define __RAY_PANEL_H__

#include <SDL2/SDL.h>
#include "Element_panel.h"
#include "Ray.h"
#include "Wall_texture.h"
#include "const.h"

class Ray_panel : public Element_panel {
public:
	Ray_panel(Ray&& ray, Wall_texture& wall_textures);
	Ray_panel(Ray_panel&& other);
	~Ray_panel();

	virtual void copy_to_rederer(SDL_Renderer& renderer) override; 
	
private:
	SDL_Texture *tex;
	Uint32 pixels[PANEL_HEIGHT];
	Ray ray;    
};

#endif