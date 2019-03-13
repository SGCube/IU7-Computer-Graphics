#include "check.h"
#include "mainwindow.h"
#include <QString>
#include <QGraphicsScene>
#include <QGraphicsSimpleTextItem>

int check_point(QString a)
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

void draw_center(float x, float y, QString text, QGraphicsScene *scene)
{
    QPen blackpen(Qt::blue);
    blackpen.setWidth(1);
    QBrush blBrush(Qt::blue);
    scene->addEllipse(x, y, 3, 3, blackpen, blBrush);
    QFont font = QFont("sans", 8);
    QString str;
    QGraphicsTextItem *label;
    str = "Центр " + text;
    label = scene->addText(str, font);
    label->setX(x);
    label->setY(y);
}
