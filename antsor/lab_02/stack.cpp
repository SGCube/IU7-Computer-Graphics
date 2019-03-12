#include "stack.h"

stack_t *create_node(void *data)
{
	stack_t *node = new stack_t;
	if (!node)
		return nullptr;
	node->data = data;
	node->next = nullptr;
	return node;
}

void push(stack_t **peak, void *data)
{
	if (!data || !peak)
		return;
	stack_t *node = create_node(data);
	if (!node)
		return;
	node->next = *peak;
	*peak = node;
}

void *pop(stack_t **peak)
{
	if (!peak || !*peak)
		return nullptr;
	stack_t *node = *peak;
	(*peak) = (*peak)->next;
	void *data = node->data;
	delete node;
	return data;
}

void clear(stack_t **peak)
{
	if (!peak)
		return;
	stack_t *cur = nullptr;
	while (*peak)
	{
		cur = *peak;
		(*peak) = (*peak)->next;
		delete cur->data;
		delete cur;
	}
}
