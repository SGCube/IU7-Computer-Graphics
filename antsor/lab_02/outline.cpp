#include <QtMath>

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

void Outline::scale(double kx, double ky, Point pm)
{
	double x, y;
	for (int i = 0; i < vertex_amount; i++)
	{
		x = vertex_ptr[i].x();
		y = vertex_ptr[i].y();
		vertex_ptr[i].setX(kx * x + (1 - kx) * pm.x());
		vertex_ptr[i].setY(ky * y + (1 - ky) * pm.y());
	}
}

void Outline::rotate(int deg, Point pc)
{
	double rad = qDegreesToRadians((double)deg);
	double x, y;
	double xc = pc.x(), yc = pc.y();
	for (int i = 0; i < vertex_amount; i++)
	{
		x = vertex_ptr[i].x();
		y = vertex_ptr[i].y();
		vertex_ptr[i].setX(xc + (x - xc) * cos(rad) + (y - yc) * sin(rad));
		vertex_ptr[i].setY(yc - (x - xc) * sin(rad) + (y - yc) * cos(rad));
	}
}

void Outline::draw(QGraphicsScene *scene)
{
	if (vertex_ptr)
	{
		QPen pen = QPen(Qt::blue, 2, Qt::SolidLine, Qt::FlatCap);
		int ibase = 0;
		double dx, dy;
		for (int i = 1; i < vertex_amount; i++)
		{
			dx = vertex_ptr[i].x() - vertex_ptr[ibase].x();
			dy = vertex_ptr[i].y() - vertex_ptr[ibase].y();
			if (abs(dx) >= 1 || abs(dy) >= 1)
			{
				scene->addLine(vertex_ptr[ibase].x(), vertex_ptr[ibase].y(),
						vertex_ptr[i].x(), vertex_ptr[i].y(), pen);
				ibase = i;
			}
		}
		if (is_closed)
			scene->addLine(vertex_ptr[vertex_amount - 1].x(),
					vertex_ptr[vertex_amount - 1].y(),
					vertex_ptr[0].x(), vertex_ptr[0].y(), pen);
	}
}

