#include "Ray.h"

Ray::Ray(const int point, const int dist) : point(point), dist(dist) {

}

Ray::Ray(Ray&& other) : point(other.point), dist(other.dist) {
}

Ray::~Ray() {
}

const int Ray::get_dist() const {
	return this->dist;
} 

const int Ray::get_point() const {
	return this->point;
}

bool Ray::operator<(Ray& other_ray) {
	return this->dist < other_ray.dist;
}	
