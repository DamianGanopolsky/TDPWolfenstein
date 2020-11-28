#include "Panel_window.h"
#include "Player.h"
#include "Event_handler.h"
#include "Map_2d.h"
#include <utility>
#include <set>
#include "Ray.h"

int main() {
	Panel_window panel;
	Player player(192, 192, 180);
	Map_2d map(player);
	Event_handler handler(player);


	while (handler.is_running()) {
		std::set<Ray> rays = std::move(map.get_player_rays());
		panel.update(std::move(rays));
		handler.handle();
	}
	return 0;
}