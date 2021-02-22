#ifndef __WALL_TEXTURE_H__
#define __WALL_TEXTURE_H__

#include <SDL2/SDL_image.h>
#include "const.h"

#define TEXTURE_HEIGHT 64 
#define TEXTURE_WIDTH 64 

class Wall_texture {
public:
	Wall_texture();
	~Wall_texture();

	int get_pixel_tex(int tex_number, int tex_x, int tex_y);

private:
	int walls_texture[TOTAL_TEXTURES_WALLS][TEXTURE_HEIGHT][TEXTURE_WIDTH];
	Uint32 get_pixel(int x, int y, SDL_Surface* image);   	
};


#endif