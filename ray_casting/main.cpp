#include "Panel_window.h"
#include "Player.h"
#include "Player_info.h"
#include "Event_handler.h"
#include "Map_2d.h"
#include "Game_element.h"
#include "Ray.h"
#include "Constant_rate_loop.h"

#include <utility>
#include <set>
#include <list>

int main() {
	Panel_window panel;
	Player player(128, 341, 90);
	Map_2d map(player);
	Event_handler handler;
	handler.handle(player);
	Constant_rate_loop crl(100);

	while (handler.is_running()) {
		std::set<Ray> rays = std::move(map.get_player_rays());
		std::list<Game_element> elements = std::move(map.get_game_elements());
		Player_info info = player.get_info();
		panel.update(std::move(rays), std::move(elements), info);
		crl.task_finished();  
	}
	return 0;
}


