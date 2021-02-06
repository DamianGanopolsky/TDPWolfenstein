#include "Map_2d.h"	
#include <utility>
#include <iostream>
#include <string>


Map_2d::Map_2d(Player& player,std::string YamlPathToMap) : player(player) {

	MapYamlParser mapyamlparser(YamlPathToMap);
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

void Map_2d::update_player_pos(int id,int pos_x,int pos_y,int angle,int status){
	//2 va a hacer que muestre a un officer
	players_state[id].pos_x=pos_x;
	players_state[id].pos_y=pos_y;
	players_state[id].vision_angle=angle;
	switch(status){
		case 0:
			players_state[id].type_id=2;
			break;
		case 1:
			players_state[id].type_id=12;
			break;
	}
}



std::list<Game_element> Map_2d::get_game_elements() {
	std::list<Game_element> elements;

	for (auto const& object : elements_map){
		
		Game_element element(object.first.first,\
		object.first.second,object.second,270,this->player);
		elements.push_back(std::move(element));
	}
	/* ACA RENDERIZO LOS DISTINTOS JUGADORES CON SUS POSICIONES ACTUALIZADAS */
	for (auto const& object : players_state){
		
		Game_element element(object.second.pos_x,object.second.pos_y,object.second.type_id,\
		object.second.vision_angle,this->player);
		elements.push_back(std::move(element));
	}
	Game_element element(150,250, 11, 270, this->player);
	Game_element element2(170,250, 12, 270, this->player);
	Game_element element3(120,250,13, 270, this->player);
	elements.push_back(std::move(element));
	elements.push_back(std::move(element2));
	elements.push_back(std::move(element3));
	return elements; 
}
