#include "outline.h"

Outline::Outline(int vn = 0, Point *ptr = nullptr, bool closed = true)
{
	vertex_amount = vn;
	vertex_ptr = ptr;
	is_closed = closed;
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

int Outline::vamount()
{
	return vertex_amount;
}

void Outline::set_vamount(int n)
{
	if (n >= 0)
		vertex_amount = n;
}

void Outline::move(int dx, int dy)
{
	for (int i = 0; i < vertex_amount; i++)
	{
		vertex_ptr[i].setX(vertex_ptr[i].x() + dx);
		vertex_ptr[i].setY(vertex_ptr[i].y() + dy);
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

