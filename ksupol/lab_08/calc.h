#ifndef CALC_H
#define CALC_H
#include "mainwindow.h"

void multiply_vectors(vector &a, vector &b, vector &res);

int sign_func(int x);

int scalar_mult(vector &a, vector &b);

QPoint calculate_P(const QPoint &p1, const QPoint &p2, double t);

#endif // CALC_H
