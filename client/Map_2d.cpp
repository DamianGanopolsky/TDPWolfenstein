#include "Map_2d.h"	
#include <utility>
#include <iostream>
#include <string>

#include <unistd.h>
#include "Yaml/YamlConfigClient.h"
#define PLAYER_DEAD 40



Map_2d::Map_2d(Player& player,std::string YamlPathToMap) : player(player),YamlMap(YamlPathToMap) {

	MapYamlParser mapyamlparser(YamlPathToMap);
	map_width=mapyamlparser.Map_Width();
	map_height=mapyamlparser.Map_Height();
	map_players=mapyamlparser.get_map_players();
	total_boxes=mapyamlparser.Map_Height()*mapyamlparser.Map_Width();
	/*std::cout << "total boxes es" << total_boxes << "height:" << mapyamlparser.Map_Height() << "width;\
	" << mapyamlparser.Map_Width() << std::endl;*/
	walls=mapyamlparser.get_boxes();
	elements_map=mapyamlparser.load_objects();
	time_last_update=std::chrono::steady_clock::now();
	
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
	float ray_width = FOV / ClientConfig.screen_width;
	float angle = this->player.get_angle() + FOV / 2;
	std::set<Ray> rays; 
	
	for (int i = 0; i < ClientConfig.screen_width; i++) {
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

void Map_2d::new_player(int id,int pos_x,int pos_y,int angle,int status){
	players_state[id].pos_x=pos_x;
	players_state[id].pos_y=pos_y;
	players_state[id].vision_angle=angle;
	players_state[id].type_id=2;
	players_state[id].weapon=1;
	players_state[id].is_shooting=0;
	players_state[id].is_moving=0;
}

void Map_2d::update_player_pos(int id,int pos_x,int pos_y,int angle,int status){
	//2 va a hacer que muestre a un officer
	players_state[id].pos_x=pos_x;
	players_state[id].pos_y=pos_y;
	players_state[id].vision_angle=angle;
	players_state[id].type_id=2;
	//players_state[id].is_moving=1;
	std::chrono::time_point<std::chrono::steady_clock> t2=std::chrono::steady_clock::now();
	std::chrono::duration<double> diff=t2-time_last_update;
	if(diff.count()>0.05){
		
		if(players_state[id].is_moving==0){
			players_state[id].is_moving=1;
		}
		else{
			players_state[id].is_moving=0;
		}
		time_last_update=std::chrono::steady_clock::now();
	}
}

void Map_2d::add_item(int pos_x,int pos_y,int item){
	elements_map[std::make_pair(pos_x,pos_y)]=item;
}

void Map_2d::add_dead_body(int id,int pos_x,int pos_y){
	//bodies_in_map[std::pair<pos_x,pos_y>]=players_state.
	body_state body;
	body.pos_x=pos_x;
	body.pos_y=pos_y;
	body.state=0;
	players_state[id].is_shooting=PLAYER_DEAD;
	switch(int(players_state[id].weapon)){
		case 0:
		case 1:{
			//bodies_in_map[std::make_pair(pos_x,pos_y)]=13;
			body.type_id=14;
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

int Map_2d::map_get_players(){
	return map_players;
}

int Map_2d::get_type_id(int weapon,int is_shooting,int is_moving){
	if(is_shooting==0){
		//return weapon;
		if(is_moving==0){
			return weapon;
		}
		else{
			if(weapon==0){
				return (is_moving*20)+1;
			}
			else{
				return (is_moving*20)+weapon;
			}
		}
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

int Map_2d::get_player_weapon(int player_id){
	return players_state[player_id].weapon;
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
		if(object.second.is_shooting==PLAYER_DEAD){
			continue;
		}
		
		Game_element element(object.second.pos_x,object.second.pos_y,\
		get_type_id(object.second.weapon,object.second.is_shooting,object.second.is_moving),\
		object.second.vision_angle,this->player);
		elements.push_back(std::move(element));
		object.second.is_shooting=0;
		std::chrono::time_point<std::chrono::steady_clock> t2=std::chrono::steady_clock::now();
		std::chrono::duration<double> diff=t2-time_last_update;
		if(diff.count()>0.1){
			object.second.is_moving=0;
		}
		//object.second.is_moving=0;
	}

	for(auto& object: bodies){
		if(object.state<3){
			object.state++;
		}
		Game_element element(object.pos_x,object.pos_y,object.type_id,object.state,this->player);
		elements.push_back(std::move(element));
	}
	return elements; 
}
