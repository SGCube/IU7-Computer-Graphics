#ifndef CHECK_H
#define CHECK_H

#include "mainwindow.h"

// проверка корректности введенных точек
int check_point(QString a);

// проверка треугольника на вырожденность
int check_tr(float x1, float y1, float x2, float y2, float x3, float y3);

int find_number(point *head, float a, float b);

#endif // CHECK_H
