#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QMouseEvent>
#include <QKeyEvent>
#include <vector>

#include "painter.h"
#include "point.h"
#include "polygon.h"

class Canvas : public QWidget
{
	Q_OBJECT
	
public:
	explicit Canvas(QWidget *parent = nullptr);
	void setCanvas(QImage* image, Painter* p);
	void setParLine(bool state);
	
protected:
	virtual void paintEvent(QPaintEvent *event);
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseMoveEvent(QMouseEvent *event);
	
private:
	QImage* img;
	Painter* painter;
	
	Point startPoint;
	Polygon clipper;
	
	bool ortDraw;
	bool isDrawing;
	bool isClipperToDraw;
	
	void addPointToClipper(Point p);
	void lockClipper();
	
signals:
	void startSegDraw(Point p);
	void breakSegDraw();
	void endSegDraw(Point p);
	void curCoord(Point p);
	
	void startClipperDraw(Point p);
	void clipperDraw(Point p);
	void endClipperDraw();
	
public slots:
	void setOrtDraw(bool state);
	void setDrawMode(bool isCutter);

};

#endif // CANVAS_H
