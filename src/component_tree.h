#pragma once

#include <component.h>
#include <render_stack.h>
#include <window.h>

struct component_tree {
	struct component *component;
	// array of pointers (array of type "component_tree *")
	component_tree **children;
	int num_children;
};

component_tree *create_component_tree() {
	component_tree *t = new component_tree();
	t->component = create_component();
	t->children = 0;
	t->num_children = 0;

	return t;
}

// TODO(Lucas): implement
void free_component_tree(component_tree *t) {
	free_component(t->component);
	delete t;
}

// TODO(Lucas): optimize array by reserving extra by doubling size each time
void component_tree_add_child(component_tree *parent, component_tree *child) {
	// make a new array 1 bigger and copy over from current array into new one
	component_tree **new_children = new component_tree*[parent->num_children + 1];
	for (int i = 0; i < parent->num_children; i++)
		new_children[i] = parent->children[i];
	// array at last index is the new child given
	new_children[parent->num_children] = child;
	// delete the old array and replace it with the new one
	delete[] parent->children;
	
	parent->children = new_children;
	parent->num_children++;
}

void component_tree_remove_child(component_tree *t, component_tree *child)
{
}

void render_component_tree(component_tree *t, render_stack *stack, window *window)
{
	if (t == 0 || stack == 0 || window == 0)
		return;
	
	render_stack_push(stack, t);
	
	while (render_stack_empty(stack) == false)
	{
		component_tree *top = render_stack_pop(stack);
		render_component(top->component, window);
		
		for (int i = 0; i < top->num_children; i++)
			render_stack_push(stack, top->children[i]);
	}
}