#include "calc.h"
#include <QPoint>

void multiply_vectors(vector &a, vector &b, vector &res)
{
    res.x = a.y * b.z - a.z * b.y;
    res.y = a.z * b.x - a.x * b.z;
    res.z = a.x * b.y - a.y * b.x;
}

int sign_func(int x)
{
    if (x > 0)
        return 1;
    if (x < 0)
        return -1;
    return 0;
}

int scalar_mult(vector &a, vector &b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

QPoint calculate_P(const QPoint &p1, const QPoint &p2, double t)
{
    QPoint res;
    res.setX(p1.x() + round((p2.x() - p1.x()) * t));
    res.setY(p1.y() + round((p2.y() - p1.y()) * t));
    return res;
}
