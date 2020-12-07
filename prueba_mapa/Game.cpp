#include "Game.h"
#include <iostream>

MovableObject* player;
Map* map;

Game::Game() {
}

Game::~Game() {}

SDL_Renderer* Game::renderer = nullptr;

void Game::init(const char* title, int width, int height, bool fullscreen) {
	int flags = 0;
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}
		isRunning = true;
	}  else {
		std::cout << "ERROR: " << SDL_GetError()  << std::endl;
	}
	Position pos(0, 0, width, height);
	player = new MovableObject("assets/imagen1.png", pos);
	map = new Map();
}

void Game::handleEvents() {
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT :
		isRunning = false;
		break;
	default:
		break;
	}
}

void Game::update() {
	SDL_Event event;
	SDL_PollEvent(&event);
	isRunning = player->update(event);
}

void Game::render() {
	SDL_RenderClear(renderer);
	map->DrawMap();
	player->render();
	SDL_RenderPresent(renderer);
}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}