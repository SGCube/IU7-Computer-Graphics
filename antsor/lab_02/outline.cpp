#include "outline.h"

Outline::Outline()
{
	pos.setX(0);
	pos.setY(0);
	vertex_amount = 0;
	vertex_ptr = nullptr;
	is_closed = true;
}

Outline::Outline(Point p)
{
	pos.setX(p.x());
	pos.setY(p.y());
	vertex_amount = 0;
	vertex_ptr = nullptr;
	is_closed = true;
}

Point *Outline::getPos()
{
	return &pos;
}

void Outline::setPos(Point p)
{
	pos.setX(p.x());
	pos.setY(p.y());
}

Point *Outline::getVertex(int i)
{
	if (!vertex_ptr || i < 0 || i >= vertex_amount)
		return nullptr;
	return &(vertex_ptr[i]);
}

void Outline::setVertex(Point p, int i)
{
	if (vertex_ptr && i >= 0 && i < vertex_amount)
	{
		vertex_ptr[i].setX(p.x());
		vertex_ptr[i].setY(p.y());
	}
}

void Outline::draw(QGraphicsScene *scene)
{
	if (vertex_ptr)
	{
		QPen pen = QPen(Qt::blue, 2, Qt::SolidLine, Qt::FlatCap);
		for (int i = 1; i < vertex_amount; i++)
			scene->addLine(vertex_ptr[i - 1].x(), vertex_ptr[i - 1].y(),
					vertex_ptr[i].x(), vertex_ptr[i].y(), pen);
		if (is_closed)
			scene->addLine(vertex_ptr[vertex_amount - 1].x(),
					vertex_ptr[vertex_amount - 1].y(),
					vertex_ptr[0].x(), vertex_ptr[0].y(), pen);
	}
}

