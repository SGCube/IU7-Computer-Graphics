#include "solve.h"

int get_plist(QTableWidget *pointTable, QPointF **plist, int rows,
			  int *no, bool *coord)
{
	/// выделение памяти под точки
	
    *plist = new QPointF[rows];
    if (!*plist)
    {
		*plist = NULL;
        return ERR_PLIST_MEM;
    }
	
    /// проверка на корректность содержимого таблицы
    
    bool correct = true;
	// строки для записи содержимого ячеек таблицы
    QString xstr, ystr;
	// координаты текущей точки
	float x, y;
	
    for (*no = 0; *no < rows; *no += 1)
    {
        xstr = pointTable->item(*no, 0)->text();
        ystr = pointTable->item(*no, 1)->text();
       
		*coord = 0;
        x = xstr.toFloat(&correct);
		if (!correct)
		{
			delete [] *plist;
			return ERR_PLIST_VAL;
		}
        
		*coord = 1;
		y = ystr.toFloat(&correct);
		if (!correct)
		{
			delete [] *plist;
			return ERR_PLIST_VAL;
		}
		
		(*plist)[*no].setX(x);
		(*plist)[*no].setY(y);
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

void error_valmsg(QLabel *msgbox, int no, bool coord)
{
	QString msg("Некорректные данные: точка №");
	msg.append(QString::number(no));
	msg.append(", координата ");
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
