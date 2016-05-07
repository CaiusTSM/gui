#include <test_config.h>

#if TEST_BITMAP == 1

#include <window.h>

#include <bitmap.h>
#include <render.h>

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
	window *window = create_window(L"bitmap test", -1, -1, 800, 600, on_resize, 0, 0);

	bitmap *bmp = create_bitmap(100, 100, 4);

	unsigned char *row = bmp->memory;

	int pitch = bmp->width * bmp->bytes_per_pixel; // 4 bytes per pixel

	for (int y = 0; y < bmp->height; y++) {
		unsigned char *pixel = row;

		for (int x = 0; x < bmp->width; x++) {
			*pixel = 0;
			pixel++;

			*pixel = 0;
			pixel++;

			*pixel = rand() % 255;
			pixel++;

			*pixel = 0;
			pixel++;
		}

		row += pitch;
	}

	load_bitmap_data(bmp, "C:/Users/Lucas/Desktop/desktop.bmp");

	while (window->is_open) {
		render_clear(window, 0, 255, 0);

		render_bitmap(window, bmp, 100, 100);

		update_window(window);
	}

	return 0;
}

#endif