#ifndef __MAP_2D__
#define __MAP_2D__

#include <unordered_map>
#include <map>
#include "Ray_shotter.h"
#include "Game_element.h"
#include "Player.h"
#include "Ray.h"
#include <set>
#include <list>
#include "const.h"
#include "Yaml/MapYamlParser.h"

class Map_2d {
public:
	explicit Map_2d(Player& player);
	Map_2d(const Map_2d& other) = delete;
	~Map_2d();

	std::set<Ray> get_player_rays(); 
	std::list<Game_element> get_game_elements(); 
	int get_wall_texture(int cuadricula);
private:
//PARED O NO
	std::map<int, bool> boxes;
	std::map<int, int> walls;
	int total_boxes;

	std::map <std::pair<int,int>,int> elements_map;
	//POSICION DEL PLAYER
	//Cada cuadricula tiene 64x64 posiciones
	Player& player; 
};

#endif
