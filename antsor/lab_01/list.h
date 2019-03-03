#ifndef LIST_H
#define LIST_H

typedef struct node list_t;

struct node
{
	void *data;
	list_t *next;
};

list_t *create_node(void *data);

int list_len(list_t *head);

list_t *list_push_back(list_t **head, void *data);
void *list_pop_back(list_t **head);

void list_clear(list_t **head);


#endif
