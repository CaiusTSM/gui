#pragma once

// declare but do not define to avoid recursive inclusion with component_tree.h
struct component_tree;
void free_component_tree(component_tree *tree);

struct render_stack
{
	component_tree **elements;
	int length;
};

render_stack *create_render_stack()
{
	render_stack *stack = new render_stack();
	stack->elements = 0;
	stack->length = 0;
	
	return stack;
}

void free_render_stack(render_stack *stack)
{
	if (stack->elements)
	{
		for (int i = 0; i < stack->length; i++)
			free_component_tree(stack->elements[i]);
		
		delete[] stack->elements;
	}
	
	delete stack;
}

void render_stack_push(render_stack *stack, component_tree *tree)
{	
	component_tree **new_list = new component_tree*[stack->length + 1];
	
	for (int i = 0; i < stack->length; i++)
		new_list[i] = stack->elements[i];
	
	new_list[stack->length] = tree;
	
	delete[] stack->elements;
	
	stack->elements = new_list;
	stack->length++;
}

component_tree *render_stack_pop(render_stack *stack)
{
	component_tree **new_list = new component_tree*[stack->length - 1];
	
	for (int i = 0; i < stack->length - 1; i++)
		new_list[i] = stack->elements[i];
	
	component_tree *top = stack->elements[stack->length - 1];
	
	delete[] stack->elements;
	
	stack->elements = new_list;
	stack->length--;
	
	return top;
}

component_tree *render_stack_top(render_stack *stack)
{
	return stack->elements[stack->length - 1];
}

bool render_stack_empty(render_stack *stack)
{
	return stack->length == 0;
}