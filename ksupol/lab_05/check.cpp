#include "check.h"
#include <QString>
#include <QColor>

int check_point(QString a)
{
    if (a[0] != '-' && (a[0] > '9' || a[0] < '0'))
        return -1;
    int i = 1;
    while (a[i] != '\0')
    {
        if (a[i] > '9' || a[i] < '0')
            return -1;
        i++;
    }
    return 0;
}

void set_color(QColor *c, int col)
{
    if (col == 0)
        c->setRgb(0, 0, 0);
    else if (col == 1)
        c->setRgb(255, 0, 0);
    else if (col == 2)
        c->setRgb(255, 191, 0);
    else if (col == 3)
        c->setRgb(251, 255, 28);
    else if (col == 4)
        c->setRgb(34, 255, 0);
    else if (col == 5)
        c->setRgb(0, 255, 230);
    else if (col == 6)
        c->setRgb(34, 0, 255);
    else
        c->setRgb(221, 0, 255);
}
