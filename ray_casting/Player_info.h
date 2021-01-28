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
	int get_weapon_status() const;
	void change_weapon_status();

private:
	int lives = 8;
	int scores = 100;
	int health = 100;
	int ammo = 100;
	int weapon = 1;
	int weapon_status = 0;  
	
};
#endif
