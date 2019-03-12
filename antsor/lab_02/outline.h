#ifndef OUTLINE_H
#define OUTLINE_H

#include <QGraphicsScene>
#include "point.h"

class Outline
{
public:
	Outline(int vn, Point *ptr, bool closed);
	
	Point *getVertex(int i);
	void setVertex(Point p, int i);
	
	int vamount();
	void set_vamount(int n);
	
	void move(int dx, int dy);
	
	void draw(QGraphicsScene *scene);
	
private:
	int vertex_amount;
	Point *vertex_ptr;
	bool is_closed;
};

#endif // OUTLINE_H
