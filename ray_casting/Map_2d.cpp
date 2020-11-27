#include "Map_2d.h"	

#define PANEL_WIDTH 320.0
#define FOV 60.0
#define TOTAL_BOX 64


Map_2d::Map_2d(Player&& player) : player(std::move(player)) {
	for (int box = 0; box < TOTAL_BOX; box++) {
		this->boxes[box] = point % 8 == 7 || point % 8 == 0 || point < 7 || point > 55;
	}
}

Map_2d::~Map_2d() {
}

std::list<Ray> Map_2d::get_player_rays() {
	float ray_width = FOV / PANEL_WIDTH;
	float angle = this->player.get_angle() - FOV / 2;  
	std::list<Ray> rays; 
	
	for (; angle < angle + FOV; angle += ray_width) {
		Ray_shotter shotter(this->boxes, angle);
		rays.insert(shotter.shoot(this->player.get_pos_x(), this->player.get_pos_y()));
	}
	return rays;
}