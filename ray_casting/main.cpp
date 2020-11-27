#include "Panel_window.h"


int main() {
	Panel_window panel();

	while (panel.is_running()) {
		panel.update();
	}
	return 0;
}