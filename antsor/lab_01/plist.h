#include <QTableWidget>

#include "mainwindow.h"

#ifndef PLIST_H
#define PLIST_H

#define OK 0
#define ERR_PLIST_MEM -1
#define ERR_PLIST_VAL -2

int get_plist(QTableWidget *pointTable, QPointF **plist, int rows,
			  int *no, bool *coord);

#endif // PLIST_H
