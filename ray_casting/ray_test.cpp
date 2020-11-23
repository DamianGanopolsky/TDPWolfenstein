#include "Ray_shotter.h"
#include "Ray.h"
#include <iostream>
#include <string>

#define POS_X 350
#define POS_Y 68
#define ANGLE 265

/*
Programa de prueba de Ray_shotter. 
*/
void print_map(std::map<int, bool>& game_map) {
	std::cout << "MAPA"<< std::endl;
	for (int i = 0; i < 64; i ++) {
		std::string block = game_map[i] ? "\033[31m(u)\033[0m": "(b)"; 
		if (i < 10) {
			std::cout << " " << i << block << " | ";
		} else {
			std::cout << i << block <<  " | ";
		}
		if (i % 8 == 7)
			std::cout << std::endl;
	}
	std::cout << std::endl;
}

bool is_wall(int point) {
	return point % 8 == 7 || point % 8 == 0 || point < 7 || point > 55;
}

int main() {
	std::map<int, bool> game_map;
	for (int cuadro = 0; cuadro < 64; cuadro++){
		game_map[cuadro] = false;
	}
	int point_unlock = (POS_Y >> 6) * 8 + (POS_X >> 6);
	game_map[point_unlock] = true;
	Ray_shotter shotter(game_map, ANGLE);
	while (point_unlock < 64 && point_unlock >= 0) {
		print_map(game_map);
		Ray ray = shotter.shoot(POS_X, POS_Y);
		if (ray.get_point() < 64 && ray.get_point() >= 0 && !is_wall(ray.get_point())) {
			std::cout << "unlock point: " << ray.get_point() << " a distancia: " << ray.get_dist() << std::endl;
			game_map[ray.get_point()] = true;
			point_unlock = ray.get_point();
		} else {
			point_unlock = -1;
		}
	}
	return 0; 
}