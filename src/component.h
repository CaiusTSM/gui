#pragma once

#include <render.h>
#include <bitmap.h>

struct padding
{
	int left;
	int right;
	int top;
	int bottom;
};

struct margin
{
	int left;
	int right;
	int top;
	int bottom;
};

enum overflow_type
{
	OT_VISIBLE,
	OT_HIDDEN,
	OT_SCROLL,
	OT_AUTO,
	OT_INITIAL,
	OT_INHERIT
};

struct overflow
{
	overflow_type x;
	overflow_type y;
};

enum position_type
{
	PT_AUTO,
	PT_LENGTH,
	PT_INITIAL,
	PT_INHERIT
};

struct style
{
	rgba color;
	rgba background_color;

	bitmap *background_image;

	struct padding padding;
	struct margin margin;

	bool visibility;

	float opacity;

	int width;
	int height;

	int min_width;
	int min_height;

	int max_width;
	int max_height;

	struct overflow overflow;

	position_type position;

	int left;
	int right;
	int top;
	int bottom;
};

struct component
{
	component *parent;
	component *children;

	struct style style;

	int x;
	int y;
	int width;
	int height;
};

component *create_component()
{
	component *com = new component();

	com->style.color.r = 255;
	com->style.color.g = 255;
	com->style.color.b = 255;
	com->style.color.a = 255;

	com->style.background_color.r = 255;
	com->style.background_color.g = 255;
	com->style.background_color.b = 255;
	com->style.background_color.a = 255;

	com->style.background_image = 0;

	com->style.padding.left = 0;
	com->style.padding.right = 0;
	com->style.padding.top = 0;
	com->style.padding.bottom = 0;

	com->style.margin.left = 0;
	com->style.margin.right = 0;
	com->style.margin.top = 0;
	com->style.margin.bottom = 0;

	com->style.visibility = true;

	com->style.opacity = 1.0f;

	com->style.width = -1;
	com->style.height = -1;

	com->style.min_width = -1;
	com->style.min_height = -1;

	com->style.max_width = -1;
	com->style.max_height = -1;

	com->style.overflow.x = OT_INHERIT;
	com->style.overflow.y = OT_INHERIT;

	com->style.position = PT_INHERIT;

	com->style.left = -1;
	com->style.right = -1;
	com->style.top = -1;
	com->style.bottom = -1;

	com->x = -1;
	com->y = -1;

	com->width = -1;
	com->height = -1;

	return com;
}

void free_component(component *com)
{
	if (com)
		delete com;
}

void render_component(component *com, window *win)
{
	render_rect(win, com->x, com->y, com->width, com->height, com->style.background_color);
}