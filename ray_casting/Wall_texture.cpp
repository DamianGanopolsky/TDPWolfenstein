#include "Wall_texture.h"
#include <iostream>

#define TEXTURE_PATH "../ray_casting/walls.png"

Wall_texture::Wall_texture() {
    this->image = IMG_Load(TEXTURE_PATH);
    if (!this->image) {
		std::cout << "ERROR: falied image load" << std::endl;
    }

    int img_width = TOTAL_TEX_X * TEXTURE_WIDTH; 
    int img_heigth = TOTAL_TEX_Y * TEXTURE_HEIGHT; 

    for (int image_y = 0; image_y < img_heigth; image_y++) {
    	for (int image_x = 0; image_x < img_width; image_x++) {
    		int tex_number = int(image_y / TEXTURE_HEIGHT) * TOTAL_TEX_X + int(image_x / TEXTURE_WIDTH);   
    		this->walls_texture[tex_number][image_y % TEXTURE_HEIGHT][image_x % TEXTURE_WIDTH] = get_pixel(image_x, image_y);
    	}
    }
}

Wall_texture::~Wall_texture() {
	if (this->image) {
		SDL_FreeSurface(this->image);
	}
}

int Wall_texture::get_pixel_tex(int tex_number, int tex_x, int tex_y) {
	return this->walls_texture[tex_number][tex_y][tex_x];
}

Uint32 Wall_texture::get_pixel(int x, int y) {
    int bpp = this->image->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)this->image->pixels + y * this->image->pitch + x * bpp;
    return p[0] | p[1] << 8 | p[2] << 16;
}
