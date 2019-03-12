#ifndef OUTLINE_H
#define OUTLINE_H

#include <QGraphicsScene>
#include "point.h"

class Outline
{
public:
	Outline();
	Outline(Point p);
	
	Point *getPos();
	void setPos(Point p);
	
	Point *getVertex(int i);
	void setVertex(Point p, int i);
	
	void draw(QGraphicsScene *scene);
	
private:
	Point pos;
	int vertex_amount;
	Point *vertex_ptr;
	bool is_closed;
};

#endif // OUTLINE_H
