#include <QDebug>

#include "canvas.h"

Canvas::Canvas(QWidget *parent) :
	QWidget(parent),
	img(nullptr),
	painter(nullptr),
	startPoint(0, 0),
	ortDraw(false),
	isDrawing(false),
	isClipperToDraw(false)
{
	setMouseTracking(true);
}

void Canvas::paintEvent(QPaintEvent *event)
{
	Q_UNUSED(event);
	painter->begin(this);
	painter->drawImage(0, 0, *img);
	painter->end();
}

void Canvas::setCanvas(QImage *image, Painter *p)
{
	img = image;
	painter = p;
}

void Canvas::setParLine(bool state)
{
	ortDraw = state;
}

void Canvas::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::RightButton && isDrawing)
	{
		isDrawing = false;
		repaint();
		if (isClipperToDraw && clipper.number_of_vertexes() > 2)
		{
			lockClipper();
			emit endClipperDraw();
		}
		else
			emit breakSegDraw();
		return;
	}
	if (event->button() != Qt::LeftButton)
		return;
	
	int x = event->pos().x();
	int y = event->pos().y();
	
	if (startPoint == Point(x, y))
		return;
	
	if (isDrawing)
	{
		if (ortDraw)
		{
			int xx = x - startPoint.x(), yy = startPoint.y() - y;
			if (yy > xx)
			{
				if (yy > -xx)
					x = startPoint.x();
				else
					y = startPoint.y();
			}
			else
			{
				if (yy > -xx)
					y = startPoint.y();
				else
					x = startPoint.x();
			}
		}
		
		painter->begin(img);
		if (isClipperToDraw)
		{
			Point plast = clipper.last_point();
			painter->drawClipper(plast.x(), plast.y(), x, y);
			addPointToClipper(Point(x, y));
			emit clipperDraw(Point(x, y));
		}
		else
		{
			isDrawing = false;
			painter->drawLineSeg(startPoint.x(), startPoint.y(), x, y);
			emit endSegDraw(Point(x, y));
		}
		painter->end();
		repaint();
	}
	else
	{
		startPoint = Point(x, y);
		isDrawing = true;
		if (isClipperToDraw)
		{
			addPointToClipper(startPoint);
			emit startClipperDraw(startPoint);
		}
		else
			emit startSegDraw(startPoint);
	}
}

void Canvas::mouseMoveEvent(QMouseEvent *event)
{
	int x = event->pos().x();
	int y = event->pos().y();
	
	emit curCoord(Point(x, y));
	
	if (!isDrawing)
		return;
	
	if (ortDraw)
	{
		int xx = x - startPoint.x(), yy = startPoint.y() - y;
		if (yy > xx)
		{
			if (yy > -xx)
				x = startPoint.x();
			else
				y = startPoint.y();
		}
		else
		{
			if (yy > -xx)
				y = startPoint.y();
			else
				x = startPoint.x();
		}
	}
	
	QImage tmpImg(*img);
	painter->begin(&tmpImg);
	if (isClipperToDraw)
	{
		Point plast = clipper.last_point();
		painter->drawClipper(plast.x(), plast.y(), x, y);
	}
	else
		painter->drawLineSeg(startPoint.x(), startPoint.y(), x, y);
	painter->end();
	
	QImage* tmpPtr = img;
	img = &tmpImg;
	repaint();
	img = tmpPtr;
}

void Canvas::addPointToClipper(Point p)
{
	painter->begin(img);
	if (clipper.number_of_vertexes() > 0)
	{
		Point plast = clipper.last_point();
		painter->drawClipper(plast.x(), plast.y(), p.x(), p.y());
	}
	clipper.add_point(p);
	painter->end();
	repaint();
}

void Canvas::lockClipper()
{
	painter->begin(img);
	
	Point pfirst = clipper.first_point();
	Point plast = clipper.last_point();
	painter->drawClipper(plast.x(), plast.y(), pfirst.x(), pfirst.y());
	
	painter->end();
	repaint();
}

void Canvas::setOrtDraw(bool state)
{
	ortDraw = state;
}

void Canvas::setDrawMode(bool isCutter)
{
	isClipperToDraw = isCutter;
}
