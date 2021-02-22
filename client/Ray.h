#ifndef __RAY_H__
#define __RAY_H__

class Ray {
public:
	Ray(const int point, const int pos_x, const int pos_y,
		const float dist, const int number);
	Ray(Ray&& other);
	~Ray();

	const float get_dist() const; 	
	const int get_point() const;
	const int get_number() const;
	const int get_pos_x() const;
	const int get_pos_y() const;
	bool operator<(const Ray& other_ray) const; 	
	bool operator>(Ray& other_ray) const;
	void set_number(int number);
	Ray get_ray_perp() const ; 	

private:
	const int point;
	const int pos_x;
	const int pos_y;
	const float dist;
	const int number; 
};

#endif