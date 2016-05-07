#include <test_config.h>

#if TEST_COMPONENT == 1

#include <window.h>
#include <component.h>

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

		update_window(window);
	}

	return 0;
}

#endif