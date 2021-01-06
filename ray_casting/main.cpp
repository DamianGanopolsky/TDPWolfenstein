#include "Panel_window.h"
#include "Player.h"
#include "Event_handler.h"
#include "Map_2d.h"
#include "Game_element.h"
#include <utility>
#include <set>
#include <list>
#include "Ray.h"

int main() {
	Panel_window panel;
	Player player(128, 341, 90);
	Map_2d map(player);
	Event_handler handler;
	handler.handle(player);

	while (handler.is_running()) {
		std::set<Ray> rays = std::move(map.get_player_rays());
		std::list<Game_element> elements = std::move(map.get_game_elements());
		panel.update(std::move(rays), std::move(elements));
	}
	return 0;
}