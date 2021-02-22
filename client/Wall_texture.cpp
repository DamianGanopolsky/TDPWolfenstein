#include "Wall_texture.h"
#include <string>
#include <iostream>
Wall_texture::Wall_texture() {

    for (int i = 0; i < TOTAL_TEXTURES_WALLS; i++) {
        std::string new_root = TEXTURE_PATH;
        new_root.append(std::to_string(i));
        new_root.append(".png");
        SDL_Surface* wall = IMG_Load(new_root.c_str());

        for (int image_y = 0; image_y < TEXTURE_HEIGHT; image_y++) {
            for (int image_x = 0; image_x < TEXTURE_WIDTH; image_x++) {
                this->walls_texture[i][image_y][image_x] = get_pixel(image_x, image_y, wall);
            }
        }
        SDL_FreeSurface(wall);
    }
}

Wall_texture::~Wall_texture() {
}

int Wall_texture::get_pixel_tex(int tex_number, int tex_x, int tex_y) {
	return this->walls_texture[tex_number][tex_y][tex_x];
}

Uint32 Wall_texture::get_pixel(int x, int y, SDL_Surface* image) {
    int bpp = image->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)image->pixels + y * image->pitch + x * bpp;
    return p[0] << 16 | p[1] << 8 | p[2];
}

