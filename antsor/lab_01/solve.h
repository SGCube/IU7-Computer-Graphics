#include <QTableWidget>
#include <QLabel>
#include "triangle.h"

#include "mainwindow.h"

#ifndef SOLVE_H
#define SOLVE_H

#define OK 0
#define ERR_PLIST_N -1
#define ERR_PLIST_MEM -2
#define ERR_PLIST_VAL -3
#define ERR_SOLV_NONE -4

int get_plist(QTableWidget *pointTable, QPointF **plist, int rows,
			  int *no, bool *coord);

void error_msg(QLabel *msgbox, int rc);

void error_valmsg(QLabel *msgbox, int no, bool coord);

void solution_msg(QLabel *msgbox, Triangle *tr, QVector2D *h, QPointF *hvertex);

bool solve(QPointF *plist, int n, Triangle *tr, QVector2D *h, QPointF *hvertex);

#endif // SOLVE_H
