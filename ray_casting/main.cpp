#include "Panel_window.h"
#include "Player.h"
#include "Event_handler.h"
#include "Map_2d.h"
#include "Game_element.h"
#include <utility>
#include <set>
#include <list>
#include "Ray.h"
#include <chrono>
#include "Constant_rate_loop.h"

int main() {
	Panel_window panel;
	Player player(128, 341, 90);
	Map_2d map(player);
	Event_handler handler;
	handler.handle(player);
	Constant_rate_loop crl(60);

	while (handler.is_running()) {
		//auto init = std::chrono::steady_clock::now();
		std::set<Ray> rays = std::move(map.get_player_rays());
		std::list<Game_element> elements = std::move(map.get_game_elements());
		panel.update(std::move(rays), std::move(elements));
		//auto end = std::chrono::steady_clock::now();
		//std::chrono::duration<double> diff = end - init;
		//std::cout << diff.count() << std::endl; 
		crl.task_finished();  
	}
	return 0;
}