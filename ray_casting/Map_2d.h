#ifndef __MAP_2D__
#define __MAP_2D__

#include <map>
#include "Ray_shotter.h"
#include "Game_element.h"
#include "Player.h"
#include "Ray.h"
#include <set>
#include <list>
#include "const.h"

class Map_2d {
public:
	explicit Map_2d(Player& player);
	Map_2d(const Map_2d& other) = delete;
	~Map_2d();

	std::set<Ray> get_player_rays(); 
	std::list<Game_element> get_game_elements(); 
private:
//PARED O NO
	std::map<int, bool> boxes;
	//POSICION DEL PLAYER
	//Cada cuadricula tiene 64x64 posiciones
	Player& player; 
};

#endif
