#ifndef QUEUE_H
#define QUEUE_H

typedef struct list_t list_node;

struct list_t
{
	void *data;
	list_node *next;
};

int push_queue(void *data, list_node **pin, list_node **pout);

void *pop_queue(list_node **pin, list_node **pout);

#endif
