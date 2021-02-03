#include "Map_2d.h"	
#include <utility>
#include <iostream>
#include <string>


Map_2d::Map_2d(Player& player) : player(player) {

	MapYamlParser mapyamlparser("../Maps/prueba_2.yaml");
	map_width=mapyamlparser.Map_Width();
	map_height=mapyamlparser.Map_Height();
	//std::cout << "map width "<< mapyamlparser.Map_Width() << "map height" << mapyamlparser.Map_Height() <<std::endl;
	total_boxes=mapyamlparser.Map_Height()*mapyamlparser.Map_Width();
	/*std::cout << "total boxes es" << total_boxes << "height:" << mapyamlparser.Map_Height() << "width;\
	" << mapyamlparser.Map_Width() << std::endl;*/
	walls=mapyamlparser.get_boxes();
	elements_map=mapyamlparser.load_objects();
	
	for (auto const& x : walls){
		if(x.second==2){
			boxes[x.first]=true;
		} 
		if(x.second==1){
			std::cout << "hay puerta en " << x.first << std::endl;
		}
	}
}

int Map_2d::get_wall_texture(int cuadricula){
	return walls[cuadricula];
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

void Map_2d::open_door(int cuadricula){
	walls[cuadricula]=2;
	boxes[cuadricula]=true;
}



std::list<Game_element> Map_2d::get_game_elements() {
	std::list<Game_element> elements;

	for (auto const& object : elements_map){
		
		Game_element element(object.first.first,\
		object.first.second,object.second,270,this->player);
		elements.push_back(std::move(element));
	}
	Game_element element(150,250, 1, 270, this->player);
	Game_element element2(170,250, 2, 270, this->player);
	Game_element element3(120,250,3, 270, this->player);
	elements.push_back(std::move(element));
	elements.push_back(std::move(element2));
	elements.push_back(std::move(element3));
	return elements; 
}
