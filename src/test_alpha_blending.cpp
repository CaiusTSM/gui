#include <test_config.h>

#if TEST_ALPHA_BLENDING == 1

#include <window.h>

#include <render.h>

void on_resize(window *window, int argc, void **args)
{
	unsigned char *row = (unsigned char *)window->bitmap_memory;

	int pitch = window->bitmap_width * 4; // 4 bytes per pixel

	for (int y = 0; y < window->bitmap_height; y++)
	{
		unsigned char *pixel = (unsigned char *)row;

		for (int x = 0; x < window->bitmap_width; x++)
		{
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

int main()
{
	window *window = create_window(L"alpha blending test", -1, -1, 800, 600, on_resize, 0, 0);

	rgba background_color = {};
	background_color.r = 255;
	background_color.g = 255;
	background_color.b = 255;
	background_color.a = 255;

	rgba red_full = {};
	red_full.r = 255;
	red_full.g = 0;
	red_full.b = 0;
	red_full.a = 255;

	//red_full = alpha_blend(red_full, background_color);

	rgba red_50 = {};
	red_50.r = 255;
	red_50.g = 0;
	red_50.b = 0;
	red_50.a = 255 / 2;

	//red_50 = alpha_blend(red_50, background_color);

	rgba red_25 = {};
	red_25.r = 255;
	red_25.g = 0;
	red_25.b = 0;
	red_25.a = 255 / 4;

	//red_25 = alpha_blend(red_25, background_color);

	rgba blue_50 = {};
	blue_50.r = 0;
	blue_50.g = 0;
	blue_50.b = 255;
	blue_50.a = 255 / 2;

	//blue_50 = alpha_blend(blue_50, background_color);

	while (window->is_open)
	{
		render_clear(window, background_color);
		render_rect(window, 100, 100, 100, 100, red_full);
		render_rect(window, 200, 100, 100, 100, red_50);
		render_rect(window, 300, 100, 100, 100, red_25);
		render_rect(window, 350, 100, 100, 100, blue_50);
		render_rect(window, 400, 150, 100, 100, 0, 255, 0, 255 / 2);

		update_window(window);
	}

	return 0;
}

#endif