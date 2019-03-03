#include "queue.h"
#include "error.h"

int push_queue(void *data, queue_t **pin, queue_t **pout)
{
	queue_t *node = new queue_t;
	if (!node)
		return ERR_Q_MEM;
	node->data = data;
	node->next = nullptr;
	if (!*pin)
	{
		*pin = node;
		*pout = node;
	}
	else
	{
		(*pin)->next = node;
		*pin = (*pin)->next;
	}
	return OK;
}

void *pop_queue(queue_t **pin, queue_t **pout)
{
	if (!*pout)
		return nullptr;
	if (*pin == *pout)
		*pin = nullptr;
	
	queue_t *tmp = *pout;
	void *data = (*pout)->data;
	
	*pout = (*pout)->next;
	delete tmp;
	
	return data;
}

void clear_queue(queue_t **pin, queue_t **pout)
{
	while (*pout)
		pop_queue(pin, pout);
}
