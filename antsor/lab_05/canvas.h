#ifndef CANVAS_H
#define CANVAS_H

#include <QGraphicsView>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <vector>
#include "polygon.h"

class Canvas : public QGraphicsScene
{
public:
	explicit Canvas(QWidget *parent = nullptr);
	~Canvas();
protected:
	void keyPressEvent(QKeyEvent *event);
	void keyReleaseEvent(QKeyEvent *event);
	void mousePressEvent(QGraphicsSceneMouseEvent *event);
	void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
private:
	QColor color_edge;
	QPen pen;
	QImage img;
	QPainter painter;
	
	std::vector<Polygon> polygons;
	Polygon new_polygon;
	
	bool parLine;
};

#endif // CANVAS_H
