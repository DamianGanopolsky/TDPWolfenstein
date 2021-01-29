#include "Map_2d.h"	
#include <utility>
#include <iostream>
#include <string>


Map_2d::Map_2d(Player& player) : player(player) {

	MapYamlParser mapyamlparser("../Maps/pruebacl.yaml");
	total_boxes=mapyamlparser.Map_Height()*mapyamlparser.Map_Width();
	std::cout << "total boxes es" << total_boxes << std::endl;
	
	boxes=mapyamlparser.get_boxes();






	//std::map <int,bool> boxes_aux=mapyamlparser.get_boxes();

		/*
	for (int box = 0; box < TOTAL_BOX; box++) {
		this->boxes[box] = !(box % 8 == 7 || box % 8 == 0 || box < 7 || box > 55 || box == 27);
	}*/
/*
	for (int box = 0; box < TOTAL_BOX; box++) {
		this->boxes[box] = !(box % 8 == 7 || box % 8 == 0 || box < 7 || box > 55 || box == 27);
	}*/

	/*
	for (int box = 0; box < TOTAL_BOX; box++) {
		this->boxes[box] = !(box % 12 == 7 || box % 12 == 0 || box < 7 || box > 55 || box == 27);
	}*/
}

Map_2d::~Map_2d() {
}

std::set<Ray> Map_2d::get_player_rays() {
	float ray_width = FOV / PANEL_WIDTH;
	float angle = this->player.get_angle() + FOV / 2;
	std::set<Ray> rays; 
	
	for (int i = 0; i < PANEL_WIDTH; i++) {
		float shotter_angle = angle < 0.0 ? 360 + angle : angle;
		shotter_angle = shotter_angle >= 360.0 ? shotter_angle - 360.0 : shotter_angle;
		Ray_shotter shotter(this->boxes, shotter_angle, i);
		int pos_x = this->player.get_pos_x();
		int pos_y = this->player.get_pos_y();
		Ray ray = shotter.shoot(pos_x, pos_y);
		rays.insert(std::move(ray));
		angle -= ray_width; 
	}
	return rays;
}

std::list<Game_element> Map_2d::get_game_elements() {
	std::list<Game_element> elements;
	Game_element element(150,250, 1, 270, this->player);
	Game_element element2(170,250, 2, 270, this->player);
	Game_element element3(120,250, 11, 270, this->player);
	elements.push_back(std::move(element));
	elements.push_back(std::move(element2));
	elements.push_back(std::move(element3));
	return elements; 
}
