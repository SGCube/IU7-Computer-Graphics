#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QMouseEvent>
#include <QKeyEvent>
#include <vector>

#include "painter.h"
#include "polygon.h"


class Canvas : public QWidget
{
	Q_OBJECT
	
public:
	explicit Canvas(QWidget *parent = nullptr);
	void canvas_set(QImage *image, std::vector<Polygon> *polygons, Polygon *pl,
					Painter *p);
	
	void add_point(Point p);
	void lock_polygon();
	void set_parline(bool s);
	
signals:
	void addPoint(Point p);
	void lockPolygon();
	void curCoord(Point p);
	void setSpan(Point p);
	
protected:
	virtual void paintEvent(QPaintEvent *event);
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseMoveEvent(QMouseEvent *event);
	
private:
	QImage *img;
	Painter *painter;
	
	std::vector<Polygon> *polygon_set;
	Polygon *new_polygon;
	
	bool parLine;
};

#endif // CANVAS_H
