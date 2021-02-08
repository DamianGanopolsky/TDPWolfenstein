#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <vector>
#include "Player_info.h"
#include "SdlClasses/SoundManager.h"
#include "../Common/protocol.h"

class Player {
public:
	Player(New_Player_Event player_initial_info);
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
	int get_id();
	void add_bullets(int bullets);
	void change_weapon(int weapon);
	void change_health(int new_health);
	void change_score(int new_score);
	void update_position_and_angle(int x,int y,float ANGLE);

private:
	SoundManager soundmanager;
	int pos_x;
	int pos_y;
	float vision_angle;
	int player_id;
	Player_info info; 
};

#endif