#include <QDebug>

#include "canvas.h"

Canvas::Canvas(QWidget *parent) :
	QWidget(parent),
	img(nullptr),
	painter(nullptr),
	polygon_set(nullptr),
	new_polygon(nullptr),
	parLine(false)
{
	setMouseTracking(true);
}

void Canvas::canvas_set(QImage *image, std::vector<Polygon> *polygons,
						Polygon *pl, Painter *p)
{
	img = image;
	painter = p;
	polygon_set = polygons;
	new_polygon = pl;
	repaint();
}

void Canvas::paintEvent(QPaintEvent *event)
{
	Q_UNUSED(event);
	painter->begin(this);
	painter->drawImage(0, 0, *img);
	painter->end();
}

void Canvas::add_point(Point p)
{
	painter->begin(img);
	painter->set_edge();
	
	if (new_polygon->number_of_vertexes() == 0)
		painter->drawPoint(p.x(), p.y());
	else
	{
		Point plast = new_polygon->last_point();
		painter->drawLine(plast.x(), plast.y(), p.x(), p.y());
	}
	new_polygon->add_point(p);
	painter->end();
	repaint();
}

void Canvas::lock_polygon()
{
	painter->begin(img);
	painter->set_edge();
	
	Point pfirst = new_polygon->first_point();
	Point plast = new_polygon->last_point();
	painter->drawLine(plast.x(), plast.y(), pfirst.x(), pfirst.y());
	
	painter->end();
	repaint();
	
	polygon_set->push_back(*new_polygon);
	new_polygon->clear();
}

void Canvas::set_parline(bool s)
{
	parLine = s;
}

void Canvas::mousePressEvent(QMouseEvent *event)
{
	int x = event->pos().x();
	int y = event->pos().y();
	
	if (event->button() == Qt::MiddleButton)
	{
		emit setSpan(Point(x, y));
		return;
	}
	
	if (event->button() == Qt::RightButton)
	{
		if (new_polygon->number_of_vertexes() > 2)
		{
			emit lockPolygon();
			lock_polygon();
		}
		return;
	}
	
	int new_x = x, new_y = y;
	
	if (parLine && new_polygon->number_of_vertexes() > 0)
	{
		Point plast = new_polygon->last_point();
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
	
	Point new_point(new_x, new_y);
	emit addPoint(new_point);
	add_point(new_point);
}

void Canvas::mouseMoveEvent(QMouseEvent *event)
{
	int x = event->pos().x();
	int y = event->pos().y();
	
	emit curCoord(Point(x, y));
	
	if (new_polygon->number_of_vertexes() == 0)
		return;
	
	Point plast = new_polygon->last_point();
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
	
	QImage tmp_img(*img);
	painter->begin(&tmp_img);
	painter->set_edge();
	painter->drawLine(plast.x(), plast.y(), new_x, new_y);
	painter->end();
	
	QImage *tmp_ptr = img;
	img = &tmp_img;
	repaint();
	img = tmp_ptr;
}
