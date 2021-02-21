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
#include <string>

struct state{
    int pos_x;
    int pos_y;
    int type_id;
    int vision_angle;
	int weapon;
	int is_shooting;
};

struct body_state{
	int pos_x;
	int pos_y;
	int type_id;
	int state;
};

class Map_2d {
public:
	explicit Map_2d(Player& player,std::string YamlPathToMap);
	Map_2d(const Map_2d& other) = delete;
	~Map_2d();

	std::set<Ray> get_player_rays(); 
	std::list<Game_element> get_game_elements(); 
	int get_wall_texture(int cuadricula);
	void open_door(int x,int y);
	void close_door(int x,int y);
	void delete_item(int x,int y);
	void update_player_pos(int id,int pos_x,int pos_y,int angle,int status);
	void update_player_texture(int id,int weapon);
	void add_dead_body(int player_id,int pos_x,int pos_y);
	void player_shoot(int id);
	int get_width();
	int get_height();
	int map_get_players();
	void add_item(int pos_x,int pos_y,int item);
	void new_player(int id,int pos_x,int pos_y,int angle,int status);
	int get_player_weapon(int player_id);
private:
//PARED O NO
	std::map<int, bool> boxes;
	//std::map<int, int> walls;
	//std::unordered_map<int, bool> boxes;
	std::map<int, int> walls;
	int total_boxes;

	int map_width;
	int map_height;
	int map_players;

	std::map <std::pair<int,int>,int> elements_map;

	std::unordered_map<int,Game_element> players_in_map;
	//std::unordered_map<int,int> elements_map;
	std::unordered_map<int,state> players_state;

	std::map <std::pair<int,int>,int> bodies_in_map;

	std::list<body_state> bodies;
	//POSICION DEL PLAYER
	//Cada cuadricula tiene 64x64 posiciones
	Player& player; 
	std::string YamlMap;

	int get_type_id(int weapon,int is_shooting);
};

#endif
