#ifndef CANVAS_H
#define CANVAS_H

#include <QGraphicsView>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <vector>

#include "mainwindow.h"
#include "painter.h"
#include "polygon.h"


class Canvas : public QGraphicsScene
{
public:
	explicit Canvas(QImage *image, std::vector<Polygon> *polygons, Polygon *pl,
					Painter *p, MainWindow *w, QWidget *parent = nullptr);
	
protected:
	void keyPressEvent(QKeyEvent *event);
	void keyReleaseEvent(QKeyEvent *event);
	void mousePressEvent(QGraphicsSceneMouseEvent *event);
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
	
private:
	MainWindow *window;
	
	QImage *img;
	Painter *painter;
	
	std::vector<Polygon> *polygon_set;
	Polygon *new_polygon;
	
	bool parLine;
};

#endif // CANVAS_H
