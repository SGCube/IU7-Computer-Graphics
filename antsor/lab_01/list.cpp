#include "list.h"

list_t *create_node(void *data)
{
	list_t *node = new list_t;
	if (!*node)
		return nullptr;
	node->data = data;
	node->next = nullptr;
	return node;
}

int list_len(list_t *head)
{
	list_t *cur = head;
	int len = 0;
	while (cur)
	{
		cur = cur->next;
		len++;
	}
	return len;
}

list_t *get_node(list_t *head, int i)
{
	if (!head)
		return nullptr;
	if (i < 1)
		return nullptr;
	list_t *cur = head;
	int j = 1;
	for (; cur && j < i; j++, cur = cur->next);
	if (!cur)
		return nullptr;
	return cur;
}

list_t *push_back(list_t **head, void *data)
{
	list_t *node = create_node(data);
	if (!node)
		return nullptr;
	
	if (!*head)
		*head = node;
	else
	{
		list_t *cur = *head;
		while(cur->next)
			cur = cur->next;
		cur->next = node;
		*head = cur;
	}
	return node;
}

void *pop_back(list_t **head)
{
	if (!head || !*head)
		return nullptr;
	
	void *data = nullptr;
	list_t *cur = *head, *prev = nullptr;
	while (cur->next)
	{
		prev = cur;
		cur = cur->next;
	}
	if (!prev)
	{
		data = (*head)->data;
		delete *head;
		*head = nullptr;
	}
	else
	{
		data = cur->data;
		delete cur;
		prev->next = nullptr;
	}
	return data;
}

void clear(list_t **head)
{
	if (!head)
		return;
	if (!*head)
		return;
	list_t *cur = *head;
	while (*head)
	{
		*head = cur->next;
		delete cur->data;
		delete cur;
		cur = *head;
	}
	*head = nullptr;
}


