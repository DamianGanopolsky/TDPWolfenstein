#ifndef GAME_H
#define GAME_H 
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "TextureManager.h"
#include "GameObject.h"
#include "MovableObject.h"
#include "Map.h"

class Game {
	public:
		Game();
		~Game();

		void init(const char* title, int width, int height, bool fullscreen);

		void handleEvents();
		void update();
		bool running() { return isRunning; }
		void render();
		void clean();
		static SDL_Renderer* renderer;

	private:
		bool isRunning = false;
		SDL_Window *window;
};
#endif