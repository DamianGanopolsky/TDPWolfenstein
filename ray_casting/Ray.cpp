#include "Ray.h"

Ray::Ray(const int point, const int dist, const int number) :
		 point(point), dist(dist), number(number) {
}

Ray::Ray(Ray&& other) : 
		point(other.point), dist(other.dist), number(other.number) {
}

Ray::~Ray() {
}

const int Ray::get_dist() const {
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
	if (other_ray.dist <= 0) {
		return false;
	}
	if (this->dist <= 0) {
		return true;
	}	
	return this->dist > other_ray.dist;
}			
