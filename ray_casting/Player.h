#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <vector>
#include "Player_info.h"
#include "SdlClasses/SoundManager.h"

class Player {
public:
	Player(int pos_x, int pos_y, float angle);
	~Player();
	
	float get_angle() const ;
	int get_pos_x() const ;
	int get_pos_y() const ;
	Player_info& get_info();
	void left_rotation();
	void right_rotation();
	void move_up();
	void move_down();
	void move_left();	
	void move_right();
	void shoot();
	void change_weapon(int weapon);
	void update_position_and_angle(int x,int y,float ANGLE);

private:
	SoundManager soundmanager;
	int pos_x;
	int pos_y;
	float vision_angle;
	Player_info info; 
};

#endif