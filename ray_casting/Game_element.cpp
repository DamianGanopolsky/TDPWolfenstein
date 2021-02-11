#include "Game_element.h"
#include <cmath>
#include "const.h"
#include <SDL2/SDL_image.h>
#include <iostream>

#define PI 3.1415
#define TOTAL_SECTIONS 8

//Type id -> No se esta usando ahora, podria servir para discriminar entre distintos 

Game_element::Game_element(int pos_x, int pos_y, int type_id, int vision_angle, Player& player) :
							type_id(type_id) {

	this->texture_section = this->get_texture_section(vision_angle, player.get_angle());

	float x = player.get_pos_x() - pos_x;
	float y = player.get_pos_y() - pos_y;
	float angle = x == 0 ? 90 : atan(abs(y / x)) * 180 / PI;

	if (x > 0 && y >= 0) {
		angle = 180 - angle;
	} else if (x > 0 && y < 0) {
		angle += 180;
	} else if (x < 0 && y < 0) {
		angle = 360 - angle; 
	}
	angle_=vision_angle;

	int ply_angle = player.get_angle() - FOV / 2;
	float  angle_min = ply_angle < 0 ? 360.0 + ply_angle : ply_angle;
	ply_angle = player.get_angle() + FOV / 2;
	float angle_max = ply_angle  >= 360 ? ply_angle - 360.0 : ply_angle;

	bool out =  angle_min > angle_max ? angle < angle_min && angle > angle_max : angle < angle_min || angle > angle_max;

	/*if (out && angle < angle_min){
		std::cout << angle << ", "<<  angle_min << std::endl;
	}*/ 

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

void Game_element::update(int pos_x, int pos_y, int TYPE_ID, int vision_angle, Player& player){
	type_id=TYPE_ID;
	this->texture_section = this->get_texture_section(vision_angle, player.get_angle());

	float x = player.get_pos_x() - pos_x;
	float y = player.get_pos_y() - pos_y;
	float angle = x == 0 ? 90 : atan(abs(y / x)) * 180 / PI;

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

	/*if (out && angle < angle_min){
		std::cout << angle << ", "<<  angle_min << std::endl;
	}*/ 

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
							pos_ray(other.pos_ray),
							type_id(other.type_id),
							texture_section(other.texture_section), 
							texture(other.texture),
							angle_(other.angle_) {
	this->dist = other.dist;
}

Game_element::~Game_element() {
}

bool Game_element::is_visible() {
	return this->pos_ray >= 0; 
} 

void Game_element::set_texture(SDL_Texture* tex) {
	this->texture = tex;
}

int Game_element::get_texture_section() {
	//DETERMINA CUAL DE TODAS LAS TEXTURAS DE ANGULO USAR, LO HARDCODEO A 0
	if(get_type_id()>13){
		std::cout << "Texture section es" << angle_ << std::endl;
		return angle_;
	}
	return this->texture_section; 
	//return 0;
}

int Game_element::get_texture_section(int element_angle, int player_angle) {
	if(get_type_id()>13){
		return angle_;
	}
	if(get_type_id()>3){
		return 0;
	}
	int element_section = this->get_angle_section(element_angle);  
	int player_section = this->get_angle_section(player_angle);
	//std::cout << "Element section es" << element_section << std::endl;
	//std::cout << "player section es" << player_section << std::endl;

	int diff = player_section - element_section + 4;
	//std::cout << "Element angle es " << element_angle << std::endl;
	//std::cout << "Texture section es" << element_angle/360 << std::endl;
	//return element_angle/360;
	int tex_sec=diff < 0 ? TOTAL_SECTIONS + diff : diff;
	if(tex_sec>7){
		return 0;
	}
	else{
		return diff < 0 ? TOTAL_SECTIONS + diff : diff; 
	}

	//std::cout << "Texture section es" << tex_sec << std::endl;

	    
}

int Game_element::get_angle_section(int angle) {
	float angle_section = 360.0 / TOTAL_SECTIONS;

	for (float i = 0; i < TOTAL_SECTIONS; i++) {
		if (angle < (i + 0.5) * angle_section) {
			return i;
		}
	}
	return 0; 
}


int Game_element::get_type_id() {
	return this->type_id; 
}

void Game_element::copy_to_rederer(SDL_Renderer& renderer) {
	SDL_Rect SrcR;

	SrcR.w = (ENEMY_HEIGHT / this->dist) * PANEL_DISTANCE;
	SrcR.h = (ENEMY_HEIGHT / this->dist) * PANEL_DISTANCE;
	SrcR.x = this->pos_ray - SrcR.w / 2;
	SrcR.y = (PANEL_HEIGHT - SrcR.w) / 2 ;
    SDL_RenderCopy(&renderer, this->texture, NULL, &SrcR);
} 
