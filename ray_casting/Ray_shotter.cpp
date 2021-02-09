#include "Ray_shotter.h"
#include <utility>
#include <math.h>
#include <iostream>
#include "Yaml/MapYamlParser.h"

#define PI 3.14159265
#define RAY_NO_VALID -1


Ray_shotter::Ray_shotter(std::map<int, bool>& game_map, const float angle,\
 const int number,int height,int width) : game_map(game_map), angle(angle), number(number),\
  map_height(height),map_width(width){
	//std::cout << "---------------"  << std::endl; 
	//std::cout << "Ray Number: " << number << std::endl;
	//MapYamlParser mapyamlparser(Yaml);
	//map_width=mapyamlparser.Map_Width();
	//map_height=mapyamlparser.Map_Height(); 
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
	//std::cout << "shoot by x: " << std::endl;  
	Ray ray_by_x = std::move(this->shoot_by_x(pos_x, pos_y));
	//std::cout << "shoot_by_y: " << std::endl; 
	Ray ray_by_y = std::move(this->shoot_by_y(pos_x, pos_y));
	if (ray_by_x > ray_by_y) {
		//std::cout << "Point: (" << ray_by_y.get_pos_x() << ", " << ray_by_y.get_pos_y() << ")"<< std::endl;  
		return ray_by_y;
	}
	//std::cout << "Point: (" << ray_by_x.get_pos_x() << ", " << ray_by_x.get_pos_y() << ")"<< std::endl; 
	return ray_by_x;
}

Ray Ray_shotter::shoot_by_y(const int pos_x, const int pos_y) {
	bool reverse = this->angle < 180.0 && this->angle > 0.0;
	float point_factor = 1.0 / (tan((this->angle) * PI / 180.0));
	point_factor = this->angle > 180.0 ? - point_factor : point_factor; 
	float dist_factor = sin(this->angle * PI / 180.0);
	return std::move(this->shoot_by(pos_y, pos_x, true, reverse, point_factor, dist_factor));
}

Ray Ray_shotter::shoot_by_x(const int pos_x, const int pos_y) {
	bool reverse = this->angle > 90.0 && this->angle < 270.0;
	float point_factor = tan((this->angle) * PI / 180.0);
	point_factor = this->angle > 270.0 || this->angle < 90.0 ? - point_factor : point_factor; 
	float dist_factor = - cos(this->angle * PI / 180.0);
	return std::move(this->shoot_by(pos_x, pos_y, false, reverse, point_factor, dist_factor));
}

Ray Ray_shotter::shoot_by(const int pos_x, const int pos_y, bool pos_exchange,
						 bool reverse, float point_factor, float dist_factor) {
	float point_x = (pos_x >> BIT_OFFSET) * SIZE_BOX;
	if (reverse) {
		point_x -= 1;
	} else {
		point_x += SIZE_BOX;
	}
	float point_y = pos_y + (abs(pos_x - point_x)) * point_factor;
	int point = pos_exchange ? this->get_point(int(point_y), int(point_x)) : this->get_point(int(point_x), int(point_y));

	while (this->valid_point(point) && this->game_map[point]) {
		int revert_factor = reverse ? -1 : 1;
		point_x += revert_factor * SIZE_BOX;
		point_y += SIZE_BOX * point_factor;
		point = pos_exchange ? this->get_point(int(point_y), int(point_x)) : this->get_point(int(point_x), int(point_y));
	}

	int dist = (pos_x - point_x) / dist_factor;
	if (!this->valid_point(point)) {
		dist = RAY_NO_VALID;
	}

	if (pos_exchange) {
		return std::move(Ray(point, int(point_y), int(point_x), dist, this->number));
	}
	return std::move(Ray(point, int(point_x), int(point_y), dist, this->number));
}

bool Ray_shotter::is_horizontal_shooter() {
	return this->angle == 0.0 || this->angle == 180.0;
}

bool Ray_shotter::is_vertical_shooter() {
	return this->angle == 90.0 || this->angle == 270.0;
}

int Ray_shotter::get_point(const int point_x, const int point_y) {
	//std::cout << "Point: (" << point_x << ", " << point_y << ")"<< std::endl; 

	if (point_x < 0 || point_y < 0) {
		return RAY_NO_VALID;
	}
	return (point_y >> BIT_OFFSET) * map_width + (point_x >> BIT_OFFSET);
}

bool Ray_shotter::valid_point(int point) const {
	return point < map_width * map_height && point >= 0;
}
