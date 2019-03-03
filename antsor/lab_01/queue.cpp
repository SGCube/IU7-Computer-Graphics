#include "queue.h"
#include "error.h"

int push_queue(void *data, list_node **pin, list_node **pout)
{
	list_node *node = new list_node;
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

void *pop_queue(list_node **pin, list_node **pout)
{
	if (!*pout)
		return nullptr;
	if (*pin == *pout)
		*pin = nullptr;
	
	list_node *tmp = *pout;
	void *data = (*pout)->data;
	
	*pout = (*pout)->next;
	delete tmp;
	
	return data;
}
