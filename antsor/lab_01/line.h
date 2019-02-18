#include <QPointF>

#ifndef LINE_H
#define LINE_H


class Line
{
public:
	float a, b, c;
	
	Line();
	Line(float ka, float kb, float kc);
	Line(QPointF p1, QPointF p2);
	float y(float x, bool *nz);
	float x(float y, bool *nz);
};

bool intersect(Line l1, Line l2, QPointF p);

#endif // LINE_H
