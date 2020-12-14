#include "Game_element.h"
#include <cmath>
#include "const.h"
#include <SDL2/SDL_image.h>
#include <iostream>

#define PI 3.1415


Game_element::Game_element(int pos_x, int pos_y, std::string img_path, Player& player) {
	this->img_path = img_path;
	float x = player.get_pos_x() - pos_x;
	float y = player.get_pos_y() - pos_y;
	//std::cout << "X: "<< x << std::endl;
	//std::cout << "Y: "<< y << std::endl;
	float angle = x == 0 ? 90 : atan(abs(y / x)) * 180 / PI;
	//std::cout << "angle: "<< angle << std::endl;

	if (x > 0 && y >= 0) {
		angle = 180 - angle;
	} else if (x > 0 && y < 0) {
		angle += 180;
	} else if (x < 0 && y < 0) {
		angle = 360 - angle; 
	}


	int ply_angle = player.get_angle() - FOV / 2;
	float  angle_min = ply_angle < 0 ? 360.0 + ply_angle : ply_angle;
	ply_angle = player.get_angle() + FOV / 2;
	float angle_max = ply_angle  >= 360 ? ply_angle - 360.0 : ply_angle;

	bool out =  angle_min > angle_max ? angle < angle_min && angle > angle_max : angle < angle_min || angle > angle_max;

	if (out) {
		this->dist = -1.0;
		this->pos_ray = -1; 
	} else {
		float angle_diff = angle > angle_max ? angle_max - angle + 360.0 : angle_max - angle;
		this->pos_ray = angle_diff / FOV * PANEL_WIDTH;

		float real_dist = sqrt(pow(x,2) + pow(y,2));
		int offset =  this->pos_ray < PANEL_WIDTH / 2 ? this->pos_ray : PANEL_WIDTH - this->pos_ray;
		this->dist = real_dist * cos((FOV / 2.0 - offset * FOV / PANEL_WIDTH) * PI / 180.0);
	} 
}

Game_element::Game_element(Game_element&& other) :
							pos_ray(other.pos_ray), img_path(other.img_path) {
	this->dist = other.dist;
}

Game_element::~Game_element() {
}

bool Game_element::is_visible() {
	return this->pos_ray >= 0; 
} 

void Game_element::copy_to_rederer(SDL_Renderer& renderer) {
	SDL_Surface *soldado_img = IMG_Load(this->img_path.c_str());
	SDL_Texture *soldado_tex = SDL_CreateTextureFromSurface(&renderer, soldado_img);
	SDL_FreeSurface(soldado_img);
	SDL_Rect SrcR;
	SrcR.w = (ENEMY_HEIGHT / this->dist) * PANEL_DISTANCE;
	SrcR.h = (ENEMY_HEIGHT / this->dist) * PANEL_DISTANCE;
	SrcR.x = this->pos_ray - SrcR.w / 2;
	SrcR.y = (PANEL_HEIGHT - SrcR.w) / 2 ;
    SDL_RenderCopy(&renderer, soldado_tex, NULL, &SrcR);
} 
