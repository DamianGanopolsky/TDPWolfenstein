#ifndef __WALL_TEXTURE_H__
#define __WALL_TEXTURE_H__

#include <SDL2/SDL_image.h>

#define TOTAL_TEX_X 6 
#define TOTAL_TEX_Y 18 
#define TEXTURE_HEIGHT 64 
#define TEXTURE_WIDTH 64 

class Wall_texture {
public:
	Wall_texture();
	~Wall_texture();

	int get_pixel_tex(int tex_number, int tex_x, int tex_y);

private:
	int walls_texture[TOTAL_TEX_X * TOTAL_TEX_Y][TEXTURE_HEIGHT][TEXTURE_WIDTH];
	SDL_Surface *image;

	Uint32 get_pixel(int x, int y);   	
};


#endif