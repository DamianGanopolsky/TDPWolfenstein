#include "Map_2d.h"	
#include <utility>


#define PANEL_WIDTH 320.0
#define FOV 60.0
#define TOTAL_BOX 64


Map_2d::Map_2d(Player&& player) : player(std::move(player)) {
	for (int box = 0; box < TOTAL_BOX; box++) {
		this->boxes[box] = !(box % 8 == 7 || box % 8 == 0 || box < 7 || box > 55);
	}
}

Map_2d::~Map_2d() {
}

std::set<Ray> Map_2d::get_player_rays() {
	float ray_width = FOV / PANEL_WIDTH;
	float angle = this->player.get_angle() + FOV / 2;
	float angle_min = angle - FOV;
	std::set<Ray> rays; 
	for (int i = 0; angle > angle_min; angle -= ray_width) {
		float shotter_angle = angle < 0.0 ? 360 + angle : angle;
		Ray_shotter shotter(this->boxes, shotter_angle, i);
		int pos_x = this->player.get_pos_x();
		int pos_y = this->player.get_pos_y();
		Ray ray = shotter.shoot(pos_x, pos_y);
		rays.insert(std::move(ray));
		i++; 
	}
	return rays;
}