#pragma once

// include basic rendering functions
#include <render.h>

struct panel {
};

panel *create_panel() {
	panel *pan = new panel();

	return pan;
}

void free_panel(panel *panel) {
	delete panel;
}

void render_panel(panel *panel) {
}