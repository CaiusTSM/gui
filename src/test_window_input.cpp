#include <test_config.h>

#if TEST_WINDOW_INPUT == 1

#include <window.h>

#include <render.h>

#include <stdio.h>

void on_resize(window *window, int argc, void **args) {
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
}

int main() {
	window *window = create_window(L"test window", -1, -1, 800, 600, on_resize, 0, 0);

	while (window->is_open) {
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

		if (window->mouse_state[0])
			rect(window, window->cursor_x, window->cursor_y, 30, 30, 255, 0, 0);
		if (window->mouse_state[1])
			rect(window, window->cursor_x, window->cursor_y, 30, 30, 0, 255, 0);
		if (window->mouse_state[2])
			rect(window, window->cursor_x, window->cursor_y, 30, 30, 255, 255, 0);

		for (int i = 0; i < window->num_keys; i++)
		{
			if (window->keyboard_state[i])
				printf("%d\n", i);
		}

		update_window(window);
	}

	return 0;
}

#endif