#include "Map_2d.h"	
#include <utility>
#include <iostream>
#include <string>


Map_2d::Map_2d(Player& player,std::string YamlPathToMap) : player(player),YamlMap(YamlPathToMap) {

	MapYamlParser mapyamlparser(YamlPathToMap);
	map_width=mapyamlparser.Map_Width();
	map_height=mapyamlparser.Map_Height();
	std::cout << "map width "<< mapyamlparser.Map_Width() << "map height" << mapyamlparser.Map_Height() <<std::endl;
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
		Ray_shotter shotter(this->boxes, shotter_angle, i,map_height,map_width);
		int pos_x = this->player.get_pos_x();
		int pos_y = this->player.get_pos_y();
		Ray ray = shotter.shoot(pos_x, pos_y);
		rays.insert(std::move(ray));
		angle -= ray_width; 
	}
	return rays;
}

void Map_2d::open_door(int x,int y){
	walls[map_width*y+x]=1;
	boxes[map_width*y+x]=true;
}

void Map_2d::close_door(int x,int y){
	walls[map_width*y+x]=2;
	boxes[map_width*y+x]=false;
}

void Map_2d::update_player_pos(int id,int pos_x,int pos_y,int angle,int status){
	//2 va a hacer que muestre a un officer
	players_state[id].pos_x=pos_x;
	players_state[id].pos_y=pos_y;
	players_state[id].vision_angle=angle;
	players_state[id].type_id=2;
}

void Map_2d::add_dead_body(int id,int pos_x,int pos_y){
	//bodies_in_map[std::pair<pos_x,pos_y>]=players_state.
	body_state body;
	body.pos_x=pos_x;
	body.pos_y=pos_y;
	body.state=0;
	std::cout << "Players state id es" << int(players_state[id].weapon) << std::endl;

	switch(int(players_state[id].type_id)){
		case 0:
		case 1:{
			//bodies_in_map[std::make_pair(pos_x,pos_y)]=13;
			body.type_id=16;
			break;
		}
		case 2:{
			body.type_id=15;
			break;
		}
		case 3:{
			bodies_in_map[std::make_pair(pos_x,pos_y)]=16;
			body.type_id=16;
			break;
		}
	}
	bodies.push_back(body);
}

void Map_2d::update_player_texture(int id,int weapon){
	players_state[id].weapon=weapon;
}

int Map_2d::get_type_id(int weapon,int is_shooting){
	if(is_shooting==0){
		return weapon;
	}
	else{
		if(weapon==0){
			return (is_shooting*10)+1;
		}
		else{
			return (is_shooting*10)+weapon;
		}
		
	}
}

void Map_2d::player_shoot(int player_id){
	if(players_state[player_id].weapon!=0){
		players_state[player_id].is_shooting=1;
	}
}

void Map_2d::delete_item(int x,int y){
	elements_map.erase(std::make_pair(x,y));
}

int Map_2d::get_height(){
	return map_height;
}

int Map_2d::get_width(){
	return map_width;
}


std::list<Game_element> Map_2d::get_game_elements() {
	std::list<Game_element> elements;

	for (auto const& object : elements_map){
		
		Game_element element(object.first.first*64,\
		object.first.second*64,object.second,270,this->player);
		elements.push_back(std::move(element));
	}
	/* ACA RENDERIZO LOS DISTINTOS JUGADORES CON SUS POSICIONES ACTUALIZADAS */
	for (auto & object : players_state){
		//std::cout << "Get type id es" << get_type_id(object.second.weapon,object.second.is_shooting) << std::endl;
		Game_element element(object.second.pos_x,object.second.pos_y,\
		get_type_id(object.second.weapon,object.second.is_shooting),\
		object.second.vision_angle,this->player);
		elements.push_back(std::move(element));
		object.second.is_shooting=0;
	}

	for(auto& object: bodies){
		if(object.state<3){
			object.state++;
		}
		Game_element element(object.pos_x,object.pos_y,object.type_id,object.state,this->player);
		elements.push_back(std::move(element));
	}
	/*Game_element element(150,250, 11, 270, this->player);
	Game_element element2(170,250, 12, 270, this->player);
	Game_element element3(120,250,13, 270, this->player);
	elements.push_back(std::move(element));
	elements.push_back(std::move(element2));
	elements.push_back(std::move(element3));*/
	return elements; 
}
