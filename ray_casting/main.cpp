#include "Panel_window.h"
#include "Player.h"
#include "Map_2d.h"
#include <utility>
#include <set>
#include "Ray.h"

int main() {
	Panel_window panel;
	Player player(192, 192, 180);
	Map_2d map(std::move(player));

	while (panel.is_running()) {
		std::set<Ray> rays = std::move(map.get_player_rays());
		panel.update(std::move(rays));
	}
	return 0;
}