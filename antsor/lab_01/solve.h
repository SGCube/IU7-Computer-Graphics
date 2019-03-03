#include <QTableWidget>
#include <QLabel>

#include "error.h"

#include "triangle.h"
#include "list.h"

#include "mainwindow.h"

#ifndef SOLVE_H
#define SOLVE_H

int get_plist(QTableWidget *pointTable, QPointF **plist, int rows);

void error_msg(QLabel *msgbox, int rc);

void error_valmsg(QLabel *msgbox, bool coord);

void solution_msg(QLabel *msgbox, Triangle *tr, QVector2D *h, QPointF *hvertex);

bool solve(QPointF *plist, int n, Triangle *tr, QVector2D *h, QPointF *hvertex);

#endif // SOLVE_H
