#ifndef __PLAYER_INFO_H__
#define __PLAYER_INFO_H__


class Player_info {
	friend class Player;
public:
	Player_info(int life,int resurrected,int score,int bullets);
	~Player_info();

	int get_lives() const;
	int get_scores() const;
	int get_health() const;
	int get_ammo() const;
	int get_weapon() const;
	int get_level() const;
	int get_weapon_status() const;
	void update_info(int life,int resurrected,int score,int bullets);
	void change_weapon_status();

	void set_initial_status(int health,int lives,int score,int ammo);

private:
	int health;
	int lives ;
	int scores;
	int ammo;
	//int scores = 0;
	//int health = 100;
	//int ammo = 100;
	
	
	
	int weapon;
	int weapon_status = 0;  
	int level=1;
	// int id_jugador= ?;
	
};
#endif
