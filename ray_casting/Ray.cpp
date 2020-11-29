#include "Ray.h"
#include <utility>
#include <cmath>

#define PANEL_WIDTH 320.0
#define FOV 60.0
#define PI 3.14159265

Ray::Ray(const int point, const float dist, const int number) :
		 point(point), dist(dist), number(number) {
}

Ray::Ray(Ray&& other) : 
		point(other.point), dist(other.dist), number(other.number) {
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
	int number_ray_offset =  this->number < PANEL_WIDTH / 2 ? this->number : PANEL_WIDTH - this->number;
	float new_dist = this->dist * cos((FOV / 2.0 - number_ray_offset * FOV / PANEL_WIDTH) * PI / 180.0);
	return Ray(this->point, new_dist, this->number);
}		
