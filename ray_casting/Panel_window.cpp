#include "Panel_window.h"
#include <iostream>

#define PANEL_WIDTH 320
#define PANEL_HEIGHT 200
#define PANEL_TITLE "WOLFENSTEIN"

Panel_window::Panel_window() {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) : running(true) {
		std::cout << "ERROR init video" << std::endln;
	}
	this->window = SDL_CreateWindow(PANEL_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, PANEL_WIDTH, PANEL_HEIGHT, 0);
	this->renderer = SDL_CreateRenderer(this->window, -1, 0);
	this->texture = SDL_CreateTexture(this->renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, PANEL_WIDTH, PANEL_HEIGHT);
	this->pixels = new Uint32[PANEL_WIDTH * PANEL_HEIGHT];
    memset(pixels, 255, PANEL_WIDTH * PANEL_HEIGHT * sizeof(Uint32));
}

Panel_window::~Panel_window() {
	if (this->pixels) {
		delete[] this->pixels;
	}
	if (this->texture) {
		SDL_DestroyTexture(this->texture);
	}
	if (this->renderer) {
		SDL_DestroyRenderer(this->renderer);
	}
	if (this->window) {
		SDL_DestroyWindow(this->window);
	}
	SDL_Quit();
}

bool Panel_window::is_running() {
	return this->running;
}

void Panel_window::update() {
    SDL_UpdateTexture(this->texture, NULL, this->pixels, PANEL_WIDTH * sizeof(Uint32));
    SDL_Event event;
    SDL_WaitEvent(&event);

    switch (event.type) {
        case SDL_MOUSEMOTION:
            {
                int mouseX = event.motion.x;
                int mouseY = event.motion.y;
                this->pixels[mouseY * PANEL_WIDTH + mouseX] = 0;
            }
            break;
        case SDL_QUIT:
            this->running = false;
            break;
    }

    SDL_RenderClear(this->renderer);
    SDL_RenderCopy(this->renderer, this->texture, NULL, NULL);
    SDL_RenderPresent(this->renderer);
}
