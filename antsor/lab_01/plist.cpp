#include "plist.h"

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
