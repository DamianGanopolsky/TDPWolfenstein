#ifndef __PLAYER_INFO_H__
#define __PLAYER_INFO_H__


class Player_info {
	friend class Player;
public:
	Player_info();
	~Player_info();

	int get_lives() const;
	int get_scores() const;
	int get_health() const;
	int get_ammo() const;
	int get_weapon() const;

private:
	int lives = 0;
	int scores = 0;
	int health = 100;
	int ammo = 50;
	int weapon = 1;  
	
};
#endif
