#ifndef __RAY_H__
#define __RAY_H__

class Ray {
public:
	Ray(const int point, const int dist);
	Ray(Ray&& other);
	~Ray();

	const int get_dist() const; 	
	const int get_point() const;
	bool operator<(Ray& other_ray); 	

private:
	const int point;
	const int dist;
};

#endif