#include "solve.h"

int get_plist(QTableWidget *pointTable, QPointF **plist, int rows)
{
	/// выделение памяти под точки
	
    *plist = new QPointF[rows];
    if (!*plist)
    {
		*plist = NULL;
        return ERR_PLIST_MEM;
    }
	
    /// создание набора точек
    
	// координаты текущей точки
	float x, y;
	
    for (int i = 0; i < rows; i += 1)
    {
        x = pointTable->item(i, 0)->text().toFloat();
		y = pointTable->item(i, 1)->text().toFloat();
		
		(*plist)[i].setX(x);
		(*plist)[i].setY(y);
    }
	return OK;
}

void error_msg(QLabel *msgbox, int rc)
{
	switch (rc)
	{
	case OK:
		break;
	case ERR_PLIST_N:
		msgbox->setText(QString("Недостаточно данных для решения задачи!"));
		break;
	case ERR_PLIST_MEM:
		msgbox->setText(QString("Ошибка выделения памяти!"));
		break;
	case ERR_PLIST_VAL:
		msgbox->setText(QString("Некорректные данные!"));
		break;
	case ERR_SOLV_NONE:
		msgbox->setText(QString("Невозможно построить треугольник!"));
		break;
	default:
		msgbox->setText(QString("Неизвестная ошибка!"));
		break;
	}
}

void error_valmsg(QLabel *msgbox, bool coord)
{
	QString msg("Некорректные данные: координата ");
	if (coord == 0)
		msg.append("X!");
	else
		msg.append("Y!");
	msgbox->setText(QString(msg));
}

void solution_msg(QLabel *msgbox, Triangle *tr, QVector2D *h, QPointF *hvertex)
{
	/// вывод решения в статусное окно
	QString msg("Треугольник:\nВершины: ");
	for (int i = 0; i < 3; i++)
	{
		msg.append("(");
		msg.append(QString::number(tr->points[i].x()));
		msg.append(", ");
		msg.append(QString::number(tr->points[i].y()));
		msg.append(") ");
	}
	msg.append("\nНаименьшая высота: ");
	msg.append(QString::number(h->length()));
	msg.append(", вершина: (");
	msg.append(QString::number(hvertex->x()));
	msg.append(", ");
	msg.append(QString::number(hvertex->y()));
	msg.append(") ");
	msgbox->setText(QString(msg));
}

bool solve(QPointF *plist, int n, Triangle *tr, QVector2D *h, QPointF *hvertex)
{
	if (!plist || n < 3)
		return false;
	
	// h - высота минимальной длины текущего треугольника
	QVector2D hcur;
	// hcurv - вершина высоты текущего треугольника
	QPointF hcurv;
	// trcur - текущий рассматриваемый треугольник
	Triangle trcur;
	// found - найдено ли хотя бы одно решение
	bool found = false;
	
	for (int i = 0; i < n - 2; i++)
		for (int j = i + 1; j < n - 1; j++)
			for (int k = j + 1; k < n; k++)
			{
				if (isTriangle(plist[i], plist[j], plist[k]))
				{
					trcur = Triangle(plist[i], plist[j], plist[k]);
					hcur = trcur.getMinHeight(&hcurv);
					if (!found || hcur.length() < h->length())
					{
						*tr = trcur;
						*h = hcur;
						*hvertex = hcurv;
						found = true;
					}
				}
			}
	
	return found;
}
