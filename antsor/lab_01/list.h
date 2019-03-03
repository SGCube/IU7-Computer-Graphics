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
list_t *get_node(list_t *head, int i);

list_t *push_back(list_t **head, void *data);
void *pop_back(list_t **head);

void clear(list_t **head);


#endif
