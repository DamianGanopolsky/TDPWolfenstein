#include "Ray.h"
#include <utility>
#include <cmath>
#include "Yaml/YamlConfigClient.h"

#define SCREEN_WIDTH 640.0
#define FOV 60.0
#define PI 3.14159265

Ray::Ray(const int point, const int pos_x, const int pos_y, 
		const float dist, const int number) :
		 point(point), pos_x(pos_x), pos_y(pos_y), dist(dist), number(number) {
}

Ray::Ray(Ray&& other) : 
		point(other.point), pos_x(other.pos_x), pos_y(other.pos_y),
		dist(other.dist), number(other.number) {
}

Ray::~Ray() {
}

const float Ray::get_dist() const {
	return this->dist;
} 

const int Ray::get_point() const {
	return this->point;
}

const int Ray::get_number() const {
	return this->number;
}

const int Ray::get_pos_x() const {
	return this->pos_x % 64;
}

const int Ray::get_pos_y() const {
	return this->pos_y % 64;
}

bool Ray::operator<(const Ray& other_ray) const {
	return this->number < other_ray.number;
}

bool Ray::operator>(Ray& other_ray) const {
	if (other_ray.dist <= 0.0) {
		return false;
	}
	if (this->dist <= 0.0) {
		return true;
	}	
	return this->dist > other_ray.dist;
}

Ray Ray::get_ray_perp() const {
	int number_ray_offset =  this->number < SCREEN_WIDTH / 2 ? this->number : SCREEN_WIDTH - this->number;
	float new_dist = this->dist * cos((FOV / 2.0 - number_ray_offset * FOV / SCREEN_WIDTH) * PI / 180.0);
	return Ray(this->point, this->pos_x, this->pos_y, new_dist, this->number);
}		
