#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QMouseEvent>
#include <QKeyEvent>
#include <vector>

#include "painter.h"
#include "point.h"

class Canvas : public QWidget
{
	Q_OBJECT
	
public:
	explicit Canvas(QImage& image, Painter& p, QWidget *parent = nullptr);
	void set_parline(bool state);
	
private:
	QImage& img;
	Painter& painter;
	
	Point startPoint;
	bool parLine;
	bool isSegDrawing;
	
signals:
	void startSegDraw(Point p);
	void breakSegDraw();
	void endSegDraw(Point p);
	void curCoord(Point p);
	
protected:
	virtual void paintEvent(QPaintEvent *event);
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseMoveEvent(QMouseEvent *event);

};

#endif // CANVAS_H
