#include "mainwindow.h"

point *MainWindow::add_to_list(point *head, float a, float b)
{
    point *node = new point;
    if (node == NULL)
        return NULL;
    node->x = a;
    node->y = b;
    node->next = NULL;
    if (head == NULL)
        return node;
    point *temp = head;
    while (temp->next != NULL)
        temp = temp->next;
    temp->next = node;
    return head;
}

void MainWindow::clear_list()
{
    point *t = head;
    int len = 0;
    while (t)
    {
        t = t->next;
        len++;
    }
    int l = len;
    for (int j = 0; j < len; j++)
    {
        t = head;
        for (int i = 0; i < l; i++)
            t = t->next;
        free(t);
        l--;
    }
    free(head);
    head = NULL;
    tri *n = head_res;
    int len_2 = 0;
    while (n)
    {
        n = n->next;
        len_2++;
    }
    int l_2 = len_2;
    for (int j = 0; j < len_2; j++)
    {
        n = head_res;
        for (int i = 0; i < l_2; i++)
            n = n->next;
        free(n);
        l_2--;
    }
    free(head_res);
    head_res = NULL;
    /*
    while(head)
    {
        point *n = head->next;
        delete head;
        head = n;
    }
    while(head_res)
    {
        tri *a = head_res->next;
        delete head_res;
        head_res = a;
    }
    */
}

point *MainWindow::delete_from_list(point *head, int d)
{
    if (d == 1)
    {
        point *a = head;
        delete a;
        head = head->next;
        amount--;
        return head;
    }
    if (d == amount)
    {
        point *t = head;
        for (int i = 0; i < d - 2; i++)
            t = t->next;
        delete t->next;
        t->next = NULL;
        return head;
    }
    point *t = head;
    for (int i = 0; i < d - 2; i++)
        t = t->next;
    point *n = head;
    for (int i = 0; i < d; i++)
        n = n->next;
    delete t->next;
    t->next = n;
    amount--;
    return head;
}

tri *MainWindow::insert_in_res(tri *head_res, float x1, float y1,
                                 float x2, float y2, float x3, float y3)
{
    tri *node = new tri;
    if (node == NULL)
        return NULL;
    node->x1 = x1;
    node->y1 = y1;
    node->x2 = x2;
    node->y2 = y2;
    node->x3 = x3;
    node->y3 = y3;
    node->next = NULL;
    if (head_res == NULL)
        return node;
    tri *a = head_res;
    while (a->next != NULL)
        a = a->next;
    a->next = node;
    return head_res;
}

void MainWindow::clear_list_res()
{
    tri *n = head_res;
    int len_2 = 0;
    while (n)
    {
        n = n->next;
        len_2++;
    }
    int l_2 = len_2;
    for (int j = 0; j < len_2; j++)
    {
        n = head_res;
        for (int i = 0; i < l_2; i++)
            n = n->next;
        free(n);
        l_2--;
    }
    free(head_res);
    head_res = NULL;
}
