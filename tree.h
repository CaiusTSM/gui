#pragma once

#include <window.h>

struct component_tree {
	// array of pointers (array of type "tree *")
	component_tree **children;
	int num_children;
	// TODO(Lucas): implement
	// component *component;
};

component_tree *create_tree() {
	component_tree *t = new component_tree();
	t->children = 0;
	t->num_children = 0;

	return t;
}

void free_component_tree(component_tree *t) {
	delete t;
}

// TODO(Lucas): optimize array by reserving extra by doubling size each time
void component_tree_add_child(component_tree *t, component_tree *child) {
	// make a new array 1 bigger and copy over from current array into new one
	component_tree **new_children = new component_tree*[t->num_children + 1];
	for (int i = 0; i < t->num_children; i++)
		new_children[i] = t->children[i];
	// array at last index is the new child given
	new_children[t->num_children] = child;
	// delete the old array and replace it with the new one
	delete[] t->children;
	t->children = new_children;
	t->num_children++;
}

// TODO(Lucas): implement
// searches tree for child and removes it (and all its children)
void component_tree_remove_child(component_tree *t, component_tree *child) {}

void render_component_tree(component_tree *t, window *window) {

}

// TODO(Lucas): implement
// void render_component_tree(component_tree *t, bitmap *bitmap) {}