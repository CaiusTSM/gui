#include <test_config.h>

#if TEST_PANEL == 1

#include <stdio.h>

#include <gui.h>

#include <str.h>

void on_resize(window *window, int argc, void *args) {
	/*
	unsigned char *row = (unsigned char *)window->bitmap_memory;

	int pitch = window->bitmap_width * 4; // 4 bytes per pixel

	for (int y = 0; y < window->bitmap_height; y++) {
	unsigned char *pixel = (unsigned char *)row;

	for (int x = 0; x < window->bitmap_width; x++) {
	*pixel = 255;
	pixel++;

	*pixel = 0;
	pixel++;

	*pixel = 0;
	pixel++;

	*pixel = 0;
	pixel++;
	}

	row += pitch;
	}
	*/
}

enum CONSTRAINT_TYPE {
	NONE,
	V_LIST,
	H_LIST,
	GRID,
	GRID_UNEVEN
};

enum OVERFLOW_TYPE {
	RUNOFF,
	V_SCROLL,
	H_SCROLL,
	VH_SCROLL,
	V_NEXT_COL,
	H_NEXT_ROW
};

struct rgb {
	unsigned char r;
	unsigned char b;
	unsigned char g;
};

rgb create_rgb(int color_hex) {
	rgb color;

	color.r = color_hex >> 24;
	color.g = (color_hex << 8) >> 24;
	color.b = (color_hex << 16) >> 24;

	return color;
}

struct panel {
	// position
	int x;
	int y;

	// dimensions
	int width;
	int height;

	// background color
	rgb background_color;

	// padding (blank space on outside) and margin (blank space on inside)
	int padding;
	int margin;

	// how to constrain the position and size of the children (the layouts such as grid, list, etc)
	CONSTRAINT_TYPE constraint_type;
	
	// the overflow type (when there are too many children in the panel it may go outside of the panel's)
	OVERFLOW_TYPE overflow_type;

	// children
	panel *child0;
	panel *child1;
	panel *child2;
	panel *child3;
};

panel *create_panel(panel* parent) {
	panel *pan = new panel();
	
	pan->x = 0;
	pan->y = 0;

	pan->width = 0;
	pan->height = 0;

	pan->background_color = create_rgb(0x0);

	pan->margin = 0;
	pan->padding = 0;

	pan->child0 = 0;
	pan->child1 = 0;
	pan->child2 = 0;
	pan->child3 = 0;

	return pan;
}

void free_panel(panel *pan) {
	delete pan;
}

void panel_constrain_children(panel *pan) {
	switch (pan->constraint_type) {
	case NONE: {
		// do nothing, let the api end user decide what to do
	}
	case V_LIST: {
		if (pan->child0) {
			pan->child0->x = pan->x + pan->margin + pan->child0->padding;
			pan->child0->y = pan->y + pan->margin + pan->child0->padding;
		}
		if (pan->child1) {
			pan->child0->x = pan->x + pan->margin + pan->child0->padding;
			pan->child0->y = pan->y + pan->margin + pan->child0->padding;
		}
		if (pan->child2) {
			pan->child0->x = pan->x + pan->margin + pan->child0->padding;
			pan->child0->y = pan->y + pan->margin + pan->child0->padding;
		}
		if (pan->child3) {
			pan->child0->x = pan->x + pan->margin + pan->child0->padding;
			pan->child0->y = pan->y + pan->margin + pan->child0->padding;
		}
	}
	case H_LIST: {
		if (pan->child0) {
			pan->child0->x = pan->x + pan->margin + pan->child0->padding;
			pan->child0->y = pan->y + pan->margin + pan->child0->padding;
		}
		if (pan->child1) {
			pan->child0->x = pan->x + pan->margin + pan->child0->padding;
			pan->child0->y = pan->y + pan->margin + pan->child0->padding;
		}
		if (pan->child2) {
			pan->child0->x = pan->x + pan->margin + pan->child0->padding;
			pan->child0->y = pan->y + pan->margin + pan->child0->padding;
		}
		if (pan->child3) {
			pan->child0->x = pan->x + pan->margin + pan->child0->padding;
			pan->child0->y = pan->y + pan->margin + pan->child0->padding;
		}
	}
	case GRID: {
		if (pan->child0) {
			pan->child0->x = pan->x + pan->margin + pan->child0->padding;
			pan->child0->y = pan->y + pan->margin + pan->child0->padding;
		}
		if (pan->child1) {
			pan->child0->x = pan->x + pan->margin + pan->child0->padding;
			pan->child0->y = pan->y + pan->margin + pan->child0->padding;
		}
		if (pan->child2) {
			pan->child0->x = pan->x + pan->margin + pan->child0->padding;
			pan->child0->y = pan->y + pan->margin + pan->child0->padding;
		}
		if (pan->child3) {
			pan->child0->x = pan->x + pan->margin + pan->child0->padding;
			pan->child0->y = pan->y + pan->margin + pan->child0->padding;
		}
	}
	default: {
		// default is vertical list
	}
	}
}

void render_panel(panel *pan, window *win) {
	rect(win, pan->x, pan->y, pan->width, pan->height, pan->background_color.r, pan->background_color.g, pan->background_color.b);

	if (pan->child0)
		render_panel(pan->child0, win);
	if (pan->child1)
		render_panel(pan->child1, win);
	if (pan->child2)
		render_panel(pan->child2, win);
	if (pan->child3)
		render_panel(pan->child3, win);
}

int main() {
	/*
	window *window = create_window(L"Test Window", -1, -1, 800, 600, on_resize, 0, 0);

	panel *pan = create_panel(0);

	pan->x = 200;
	pan->y = 100;

	pan->width = 400;
	pan->height = 400;

	pan->r = 200;
	pan->g = 200;
	pan->b = 200;

	panel *child0 = create_panel(pan);

	pan->child0 = child0;

	panel *child1 = create_panel(pan);

	pan->child1 = child1;

	panel *child2 = create_panel(pan);

	pan->child2 = child2;

	panel *child3 = create_panel(pan);

	pan->child3 = child3;

	while (window->is_open) {
		render_clear(window, 36, 254, 185);

		render_panel(pan, window);

		update_window(window);
	}
	*/

	/*
	string str = "Hello World!";

	string str2;

	str2 = str;

	str2 += "test";

	str2 += str;

	printf("%s", str2.data);

	getchar();
	*/

	return 0;
}

#endif