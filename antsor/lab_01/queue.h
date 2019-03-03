#ifndef QUEUE_H
#define QUEUE_H

typedef struct queue_node queue_t;

struct queue_node
{
	void *data;
	queue_t *next;
};

int push_queue(void *data, queue_t **pin, queue_t **pout);

void *pop_queue(queue_t **pin, queue_t **pout);

void clear_queue(queue_t **pin, queue_t **pout);

#endif
