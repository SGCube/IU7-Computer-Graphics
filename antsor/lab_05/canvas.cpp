#include <QDebug>

#include "canvas.h"

Canvas::Canvas(QWidget *parent) :
	QGraphicsScene(parent),
	color_edge(0, 0, 0),
	pen(color_edge),
	img(640, 640, QImage::Format_RGB32),
	painter(&img)
{
	img.fill(QColor(255, 255, 255));
	addPixmap(QPixmap::fromImage(img));
	
	painter.setPen(pen);
	setSceneRect(0, 0, 640, 640);
	
	parLine = false;
}

Canvas::~Canvas()
{
	polygons.clear();
}

void Canvas::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Shift)
		parLine = true;
}

void Canvas::keyReleaseEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Shift)
		parLine = false;
}

void Canvas::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	int x = event->scenePos().x();
	int y = event->scenePos().y();
	
	if (event->button() == Qt::RightButton)
	{
		addPixmap(QPixmap::fromImage(img));
		polygons.push_back(new_polygon);
		new_polygon.clear();
		return;
	}
	
	int new_x = x, new_y = y;
	if (new_polygon.number_of_vertexes() == 0)
		painter.drawPoint(x, y);
	else
	{
		Point plast = new_polygon.last_point();
		if (parLine)
		{
			int xx = x - plast.x(), yy = plast.y() - y;
			if (yy > xx)
			{
				if (yy > -xx)
					new_x = plast.x();
				else
					new_y = plast.y();
			}
			else
			{
				if (yy > -xx)
					new_y = plast.y();
				else
					new_x = plast.x();
			}
		}
		painter.drawLine(plast.x(), plast.y(), new_x, new_y);
	}
	addPixmap(QPixmap::fromImage(img));
	
	new_polygon.add_point(Point(new_x, new_y));
}

void Canvas::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
	Point pfirst = new_polygon.first_point();
	Point plast = new_polygon.last_point();
	painter.drawLine(plast.x(), plast.y(), pfirst.x(), pfirst.y());
	
	addPixmap(QPixmap::fromImage(img));
	
	polygons.push_back(new_polygon);
	new_polygon.clear();
}

void Canvas::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	if (new_polygon.number_of_vertexes() > 0)
	{
		painter.end();
		
		QImage tmp_img(img);
		painter.begin(&tmp_img);
		
		Point plast = new_polygon.last_point();
		
		int x = event->scenePos().x();
		int y = event->scenePos().y();
		int new_x = x, new_y = y;
		if (parLine)
		{
			int xx = x - plast.x(), yy = plast.y() - y;
			if (yy > xx)
			{
				if (yy > -xx)
					new_x = plast.x();
				else
					new_y = plast.y();
			}
			else
			{
				if (yy > -xx)
					new_y = plast.y();
				else
					new_x = plast.x();
			}
		}
		painter.drawLine(plast.x(), plast.y(), new_x, new_y);
		addPixmap(QPixmap::fromImage(tmp_img));
		
		painter.end();
		painter.begin(&img);
	}
}
