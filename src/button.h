#pragma once

#include <component_tree.h>

struct button
{
	component_tree *node;
};

button *create_button()
{
	button *b = new button();
	b->node = create_component_tree();
	
	return b;
}

void free_button(button *b)
{
	free_component_tree(b->node);
	delete b;
}

void render_button(button *b, window* win)
{
	
}