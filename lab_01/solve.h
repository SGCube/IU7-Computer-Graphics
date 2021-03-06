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

void solution_msg(QLabel *msgbox, list_t *res);

list_t *solve(Point *plist, int n);

#endif // SOLVE_H
