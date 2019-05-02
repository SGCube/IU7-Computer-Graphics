#ifndef CANVAS_H
#define CANVAS_H

#include <QGraphicsView>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <vector>

#include "polygon.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

class Canvas : public QGraphicsScene
{
public:
	explicit Canvas(QImage *image, std::vector<Polygon> *polygons,
					MainWindow *w, QWidget *parent = nullptr);
	
protected:
	void keyPressEvent(QKeyEvent *event);
	void keyReleaseEvent(QKeyEvent *event);
	void mousePressEvent(QGraphicsSceneMouseEvent *event);
	void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
	
private:
	QColor color_edge;
	QPen pen;
	QPainter painter;
	
	std::vector<Polygon> *polygon_set;
	Polygon new_polygon;
	
	bool parLine;
	
	QImage *img;
	MainWindow *window;
};

#endif // CANVAS_H
