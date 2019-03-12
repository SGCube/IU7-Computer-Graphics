#ifndef STACK_H
#define STACK_H

typedef struct stack stack_t;

struct stack
{
	void *data;
	stack_t *next;
};

stack_t *create_node(void *data);
void push(stack_t **peak, void *data);
void *pop(stack_t **peak);
void clear(stack_t **peak);

#endif // STACK_H
