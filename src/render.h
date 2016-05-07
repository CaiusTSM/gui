#pragma once

#include <window.h>
#include <bitmap.h>

struct rgba
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
};

void render_clear(window *window, unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	float r1 = r / 255.0f;
	float g1 = g / 255.0f;
	float b1 = b / 255.0f;
	float a1 = a / 255.0f;

	int bytes_per_pixel = 4;

	unsigned char *row = (unsigned char *)window->bitmap_memory;

	int pitch = window->bitmap_width * bytes_per_pixel;

	for (int i = 0; i < window->bitmap_height; i++)
	{
		unsigned char *pixel = (unsigned char *)row;

		for (int j = 0; j < window->bitmap_width; j++)
		{
			float b2 = pixel[0] / 255.0f;
			float g2 = pixel[1] / 255.0f;
			float r2 = pixel[2] / 255.0f;
			float a2 = pixel[3] / 255.0f;

			pixel[0] = (unsigned char)((b1 * a1 + b2 * (1 - a1)) * 255.0f);
			pixel[1] = (unsigned char)((g1 * a1 + g2 * (1 - a1)) * 255.0f);
			pixel[2] = (unsigned char)((r1 * a1 + r2 * (1 - a1)) * 255.0f);
			pixel[3] = (unsigned char)((a1 + a2 * (1 - a1)) * 255.0f);

			pixel += bytes_per_pixel;
		}

		row += pitch;
	}
}

void render_clear(window *window, rgba color)
{
	float r1 = color.r / 255.0f;
	float g1 = color.g / 255.0f;
	float b1 = color.b / 255.0f;
	float a1 = color.a / 255.0f;

	int bytes_per_pixel = 4;

	unsigned char *row = (unsigned char *)window->bitmap_memory;

	int pitch = window->bitmap_width * bytes_per_pixel;

	for (int i = 0; i < window->bitmap_height; i++)
	{
		unsigned char *pixel = (unsigned char *)row;

		for (int j = 0; j < window->bitmap_width; j++)
		{
			float b2 = pixel[0] / 255.0f;
			float g2 = pixel[1] / 255.0f;
			float r2 = pixel[2] / 255.0f;
			float a2 = pixel[3] / 255.0f;

			pixel[0] = (unsigned char)((b1 * a1 + b2 * (1 - a1)) * 255.0f);
			pixel[1] = (unsigned char)((g1 * a1 + g2 * (1 - a1)) * 255.0f);
			pixel[2] = (unsigned char)((r1 * a1 + r2 * (1 - a1)) * 255.0f);
			pixel[3] = (unsigned char)((a1 + a2 * (1 - a1)) * 255.0f);

			pixel += bytes_per_pixel;
		}

		row += pitch;
	}
}

void render_rect(window *window, int x, int y, int width, int height, unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	if (width > 0 && height > 0)
	{
		float r1 = r / 255.0f;
		float g1 = g / 255.0f;
		float b1 = b / 255.0f;
		float a1 = a / 255.0f;

		if (x < 0)
		{
			width += x;
			x = 0;
		}
		if (y < 0)
		{
			height += y;
			y = 0;
		}

		int bytes_per_pixel = 4;

		unsigned char *row = (unsigned char *)window->bitmap_memory;

		int pitch = window->bitmap_width * bytes_per_pixel;

		row += pitch * y;

		for (int i = 0; i < height && y + i < window->bitmap_height; i++)
		{
			unsigned char *pixel = (unsigned char *)row;
			pixel += x * bytes_per_pixel;

			for (int j = 0; j < width && x + j < window->bitmap_width; j++)
			{
				float b2 = pixel[0] / 255.0f;
				float g2 = pixel[1] / 255.0f;
				float r2 = pixel[2] / 255.0f;
				float a2 = pixel[3] / 255.0f;

				pixel[0] = (unsigned char)((b1 * a1 + b2 * (1 - a1)) * 255.0f);
				pixel[1] = (unsigned char)((g1 * a1 + g2 * (1 - a1)) * 255.0f);
				pixel[2] = (unsigned char)((r1 * a1 + r2 * (1 - a1)) * 255.0f);
				pixel[3] = (unsigned char)((a1 + a2 * (1 - a1)) * 255.0f);

				pixel += bytes_per_pixel;
			}

			row += pitch;
		}
	}
}

void render_rect(window *window, int x, int y, int width, int height, rgba color)
{
	if (width > 0 && height > 0)
	{
		float r1 = color.r / 255.0f;
		float g1 = color.g / 255.0f;
		float b1 = color.b / 255.0f;
		float a1 = color.a / 255.0f;

		if (x < 0)
		{
			width += x;
			x = 0;
		}
		if (y < 0)
		{
			height += y;
			y = 0;
		}

		int bytes_per_pixel = 4;

		unsigned char *row = (unsigned char *)window->bitmap_memory;

		int pitch = window->bitmap_width * bytes_per_pixel;

		row += pitch * y;

		for (int i = 0; i < height && y + i < window->bitmap_height; i++)
		{
			unsigned char *pixel = (unsigned char *)row;
			pixel += x * bytes_per_pixel;

			for (int j = 0; j < width && x + j < window->bitmap_width; j++)
			{
				float b2 = pixel[0] / 255.0f;
				float g2 = pixel[1] / 255.0f;
				float r2 = pixel[2] / 255.0f;
				float a2 = pixel[3] / 255.0f;

				pixel[0] = (unsigned char)((b1 * a1 + b2 * (1 - a1)) * 255.0f);
				pixel[1] = (unsigned char)((g1 * a1 + g2 * (1 - a1)) * 255.0f);
				pixel[2] = (unsigned char)((r1 * a1 + r2 * (1 - a1)) * 255.0f);
				pixel[3] = (unsigned char)((a1 + a2 * (1 - a1)) * 255.0f);

				pixel += bytes_per_pixel;
			}

			row += pitch;
		}
	}
}

void render_bitmap(window *win, bitmap *bmp, int x, int y)
{
	rgba pixel = {};

	int width = bmp->width;
	int height = bmp->height;

	if (x < 0)
	{
		width += x;
		x = 0;
	}
	if (y < 0)
	{
		height += y;
		y = 0;
	}
	if (x + width > win->bitmap_width)
	{
		width -= (win->bitmap_width - x + width);
	}
	if (y + height > win->bitmap_height)
	{
		height -= (win->bitmap_height - y + height);
	}

	int bytes_per_pixel = 4;

	unsigned char *row = (unsigned char *)win->bitmap_memory;
	unsigned char *bitmap_row = bmp->memory;

	int pitch = win->bitmap_width * bytes_per_pixel;
	int bitmap_pitch = bmp->width * bmp->bytes_per_pixel;

	row += pitch * y;

	for (int i = 0; i < height; i++)
	{
		unsigned char *pixel = row;
		unsigned char *bitmap_pixel = bitmap_row;
		pixel += x * bytes_per_pixel;

		for (int j = 0; j < width; j++)
		{
			*pixel = *bitmap_pixel;
			pixel++;
			bitmap_pixel++;

			*pixel = *bitmap_pixel;
			pixel++;
			bitmap_pixel++;

			*pixel = *bitmap_pixel;
			pixel++;
			bitmap_pixel++;

			*pixel = *bitmap_pixel;
			pixel++;
			bitmap_pixel++;
		}

		row += pitch;
		bitmap_row += bitmap_pitch;
	}
}

rgba alpha_blend(rgba above, rgba below)
{
	rgba color = {};

	float r1 = above.r / 255.0f;
	float g1 = above.g / 255.0f;
	float b1 = above.b / 255.0f;
	float a1 = above.a / 255.0f;

	float r2 = below.r / 255.0f;
	float g2 = below.g / 255.0f;
	float b2 = below.b / 255.0f;
	float a2 = below.a / 255.0f;

	float r = r1 * a1 + r2 * (1 - a1);
	float g = g1 * a1 + g2 * (1 - a1);
	float b = b1 * a1 + b2 * (1 - a1);
	float a = a1 + a2 * (1 - a1);

	color.r = (unsigned char)(r * 255);
	color.g = (unsigned char)(g * 255);
	color.b = (unsigned char)(b * 255);
	color.a = (unsigned char)(a * 255);

	return color;
}

// TODO(lucas): implement unless unused
bool color_from_string(const char *str, int str_length, rgba *color_out)
{
	if (str_length > 0)
	{
		if (str[0] == '#')
		{
			if (str_length == 7)
			{
				return false;
			}
		}
	}

	return false;
}