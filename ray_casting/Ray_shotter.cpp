#include "Ray_shotter.h"
#include <utility>
#include <math.h>
#include <iostream>

#define PI 3.14159265
#define SIZE_BOX 64 //Este valor debe ser una potencia de base 2
#define BIT_OFFSET 6 //Este valor debe ser el Log de base 2 de SIZE_BOX
#define WIDTH_GAME_MAP 8

Ray_shotter::Ray_shotter(std::map<int, bool>& game_map, const float angle) :
						game_map(game_map), angle(angle) {
}

Ray_shotter::~Ray_shotter() {
}


Ray Ray_shotter::shoot(const int pos_x, const int pos_y) {
	if (this->is_horizontal_shooter()) {
		return std::move(this->shoot_by_x(pos_x, pos_y));
	} 
	if (this->is_vertical_shooter()) {
		return std::move(this->shoot_by_y(pos_x, pos_y));
	} 
	Ray ray_by_x = std::move(this->shoot_by_x(pos_x, pos_y));
	Ray ray_by_y = std::move(this->shoot_by_y(pos_x, pos_y));
	if (ray_by_x < ray_by_y) {
		return ray_by_x;
	}
	return ray_by_y;
}

Ray Ray_shotter::shoot_by_y(const int pos_x, const int pos_y) {
	bool reverse = this->angle < 180.0 && this->angle > 0.0;
	float point_factor = 1.0 / (tan((this->angle) * PI / 180.0));
	float dist_factor = sin(this->angle * PI / 180.0);
	return std::move(this->shoot_by(pos_y, pos_x, true, reverse, point_factor, dist_factor));
}

Ray Ray_shotter::shoot_by_x(const int pos_x, const int pos_y) {
	bool reverse = this->angle > 90.0 && this->angle < 270.0;
	float point_factor = tan((this->angle) * PI / 180.0);
	float dist_factor = - cos(this->angle * PI / 180.0);
	return std::move(this->shoot_by(pos_x, pos_y, false, reverse, point_factor, dist_factor));
}

Ray Ray_shotter::shoot_by(const int pos_x, const int pos_y, bool pos_exchange,
						 bool reverse, float point_factor, float dist_factor) {
	int point_x = (pos_x >> BIT_OFFSET) * SIZE_BOX;
	if (reverse) {
		point_x -= 1;
	} else {
		point_x += SIZE_BOX;
	}
	int point_y = pos_y + ((pos_x - point_x)) * point_factor;
	int point = pos_exchange ? this->get_point(point_y, point_x) : this->get_point(point_x, point_y);
	while (this->game_map[point]) {
		int revert_factor = reverse ? -1 : 1;
		point_x += revert_factor * SIZE_BOX;
		point_y += revert_factor * SIZE_BOX * point_factor;
		point = pos_exchange ? this->get_point(point_y, point_x) : this->get_point(point_x, point_y);
	}
	int dist = (pos_x - point_x) / dist_factor;
	return std::move(Ray(point, dist));
}

bool Ray_shotter::is_horizontal_shooter() {
	return this->angle == 0.0 || this->angle == 180.0;
}

bool Ray_shotter::is_vertical_shooter() {
	return this->angle == 90.0 || this->angle == 270.0;
}

int Ray_shotter::get_point(const int point_x, const int point_y) {
	return (point_y >> BIT_OFFSET) * WIDTH_GAME_MAP + (point_x >> BIT_OFFSET);
}
