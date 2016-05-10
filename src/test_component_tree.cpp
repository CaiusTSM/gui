#include <test_config.h>

#if TEST_COMPONENT_TREE == 1

#include <window.h>
#include <component_tree.h>

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
	window *window = create_window(L"test component tree", -1, -1, 800, 800, on_resize, 0, 0);
	
	component_tree *root = create_component_tree();
	root->component->x = 100;
	root->component->y = 100;
	root->component->width = 500;
	root->component->height = 500;
	root->component->style.background_color.r = 100;
	root->component->style.background_color.g = 100;
	root->component->style.background_color.b = 100;
	
	render_stack *stack = create_render_stack();
	
	component_tree *child1 = create_component_tree();
	child1->component->x = 120;
	child1->component->y = 120;
	child1->component->width = 100;
	child1->component->height = 100;
	component_tree *child2 = create_component_tree();
	child2->component->x = 120;
	child2->component->y = 480;
	child2->component->width = 100;
	child2->component->height = 100;
	component_tree *child3 = create_component_tree();
	child3->component->x = 480;
	child3->component->y = 120;
	child3->component->width = 100;
	child3->component->height = 100;
	component_tree *child4 = create_component_tree();
	child4->component->x = 480;
	child4->component->y = 480;
	child4->component->width = 100;
	child4->component->height = 100;
	
	component_tree_add_child(root, child1);
	component_tree_add_child(root, child2);
	component_tree_add_child(root, child3);
	component_tree_add_child(root, child4);
	
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
		
		render_component_tree(root, stack, window);
		
		child1->component->style.background_color.r = 255;
		
		if (
		window->cursor_x >= 120 && window->cursor_x <= 220
		&& window->cursor_y >= 120 && window->cursor_y <= 220
		&& component_tree_is_child(root, child1)
		)
		{
			if (window->mouse_state[0])
				component_tree_remove_child(root, child1);
			else
				child1->component->style.background_color.r = 0;
		}

		update_window(window);
	}

	return 0;
}

#endif