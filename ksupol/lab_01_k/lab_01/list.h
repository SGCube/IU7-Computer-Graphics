#ifndef LIST_H
#define LIST_H

#include "mainwindow.h"

extern point *head;
extern tri *head_res;
extern int amount;

// добавление элемента в список точек
point *add_to_list(point *head, float a, float b);

// очистка списка точек
void clear_list();

// удаление элемента из списка точек
point *delete_from_list(point *head, int d);

// добавление треугольника в список-результат
tri *insert_in_res(tri *head_res, float x1, float y1,
                                 float x2, float y2, float x3, float y3);

// очистка списка-результата
void clear_list_res();

// изменение значения в списке
point *change_element(point *head, int a_int, QString new_x, QString new_y);
#endif // LIST_H
