#include "mainwindow.h"

int MainWindow::check_point(QString a)
{
    if (a[0] != '-' && (a[0] > '9' || a[0] < '0'))
        return -1;
    int flag = 0;
    for (int i = 1; i < a.length(); i++)
    {
        if (a[i] == '.' && flag == 0)
            flag = 1;
        else if (a[i] == '.' && flag != 0)
            return -1;
        else if (a[i] < '0' || a[i] > '9')
            return -1;

    }
    if (a[a.length() - 1] == '.')
        return -1;
    return 0;
}

int MainWindow::check_tr(float x1, float y1, float x2, float y2, float x3, float y3)
{
    if (x1 == x2 && x1 == x3 && x2 == x3 &&
            y1 == y2 && y1 == y3 && y2 == y3)
        return -1;
    float a = sqrt(qPow(x2 - x1, 2) + qPow(y2 - y1, 2));
    float b = sqrt(qPow(x3 - x1, 2) + qPow(y3 - y1, 2));
    float c = sqrt(qPow(x3 - x2, 2) + qPow(y3 - y2, 2));

    if (a == b + c || b == a + c || c == a + b)
        return -2;
    return 0;
}
