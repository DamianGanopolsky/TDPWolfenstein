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

struct state{
    int pos_x;
    int pos_y;
    int type_id;
    int vision_angle;
};

class Map_2d {
public:
	explicit Map_2d(Player& player);
	Map_2d(const Map_2d& other) = delete;
	~Map_2d();

	std::set<Ray> get_player_rays(); 
	std::list<Game_element> get_game_elements(); 
	int get_wall_texture(int cuadricula);
	void open_door(int cuadricula);
	void update_player_pos(int id,int pos_x,int pos_y,int angle);
private:
//PARED O NO
	std::map<int, bool> boxes;
	//std::map<int, int> walls;
	//std::unordered_map<int, bool> boxes;
	std::map<int, int> walls;
	int total_boxes;

	int map_width;
	int map_height;

	std::map <std::pair<int,int>,int> elements_map;

	std::unordered_map<int,Game_element> players_in_map;
	//std::unordered_map<int,int> elements_map;
	std::unordered_map<int,state> players_state;
	//POSICION DEL PLAYER
	//Cada cuadricula tiene 64x64 posiciones
	Player& player; 
};

#endif
