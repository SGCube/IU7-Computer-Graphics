#include <QDebug>

#include "canvas.h"

Canvas::Canvas(QImage *image, std::vector<Polygon> *polygons, Polygon *pl,
			   Painter *p, MainWindow *w, QWidget *parent) :
	QGraphicsScene(parent),
	window(w),
	img(image),
	painter(p),
	polygon_set(polygons),
	new_polygon(pl),
	parLine(false)
{
	setSceneRect(0, 0, 640, 640);
	addPixmap(QPixmap::fromImage(*img));
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
	if (event->button() == Qt::RightButton)
		return;
	
	int x = event->scenePos().x();
	int y = event->scenePos().y();
	int new_x = x, new_y = y;
	
	painter->begin(img);
	painter->set_edge();
	
	if (new_polygon->number_of_vertexes() == 0)
		painter->drawPoint(x, y);
	else
	{
		Point plast = new_polygon->last_point();
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
		painter->drawLine(plast.x(), plast.y(), new_x, new_y);
	}
	addPixmap(QPixmap::fromImage(*img));
	
	painter->end();
	
	new_polygon->add_point(Point(new_x, new_y));
	
	if (window)
	{
		window->add_point(Point(new_x, new_y));
		if (new_polygon->number_of_vertexes() > 2)
			window->lock_disable(false);
	}
}

void Canvas::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
	if (new_polygon->number_of_vertexes() < 3)
		return;
	
	Point pfirst = new_polygon->first_point();
	Point plast = new_polygon->last_point();
	
	painter->begin(img);
	painter->set_edge();
	
	painter->drawLine(plast.x(), plast.y(), pfirst.x(), pfirst.y());
	addPixmap(QPixmap::fromImage(*img));
	
	painter->end();
	
	polygon_set->push_back(*new_polygon);
	new_polygon->clear();
	
	if (window)
	{
		window->lock_disable(true);
		window->end_polygon();
	}
}

void Canvas::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	if (new_polygon->number_of_vertexes() == 0)
		return;
	
	QImage tmp_img(*img);
	painter->begin(&tmp_img);
	painter->set_edge();
	
	Point plast = new_polygon->last_point();
	
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
	painter->drawLine(plast.x(), plast.y(), new_x, new_y);
	addPixmap(QPixmap::fromImage(tmp_img));
	
	painter->end();
}
