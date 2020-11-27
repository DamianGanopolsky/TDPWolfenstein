#ifndef __MAP_2D__
#define __MAP_2D__

#include <map>
#include "Ray_shotter.h"
#include "Player.h"
#include "Ray.h"

class Map_2d {
public:
	explicit Map_2d(Player&& player);
	Map_2d(const Map_2d& other) = delete;
	~Map_2d();

	std::list<Ray> get_player_rays(); 
private:
	std:map<int, bool>s boxes;
	Player player; 
};

#endif
