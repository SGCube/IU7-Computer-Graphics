#include <QTableWidget>
#include <QLabel>

#include "error.h"

#include "point.h"
#include "triangle.h"
#include "list.h"

#include "mainwindow.h"

#ifndef SOLVE_H
#define SOLVE_H

int get_plist(QTableWidget *pointTable, Point **plist, int rows);

void error_msg(QLabel *msgbox, int rc);

void error_valmsg(QLabel *msgbox, bool coord);

//void solution_msg(QLabel *msgbox, Triangle *tr, QVector2D *h, QPointF *hvertex);

bool solve(Point *plist, int n, Triangle *tr);

#endif // SOLVE_H
