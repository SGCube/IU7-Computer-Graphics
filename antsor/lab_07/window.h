#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <vector>

#include "point.h"
#include "lineseg.hpp"
#include "canvas.h"

namespace Ui {
class Window;
}

class Window : public QMainWindow
{
	Q_OBJECT
	
public:
	explicit Window(QWidget *parent = nullptr);
	~Window();
	
protected:
	void keyPressEvent(QKeyEvent *event);
	void keyReleaseEvent(QKeyEvent *event);
	
private:
	Ui::Window *ui;
	
	QImage img;
	Painter painter;
	
	std::vector<LineSeg> lineSegments;
	Point startPoint;
	
	QColor colorLine;
	QColor colorCutter;
	QColor colorCutted;
	
	QString coordText(Point& p);
	
public slots:
	void getStartPoint(Point p);
	void resetStartPoint();
	void getEndPoint(Point p);
	void getCurCoord(Point coord);
};

#endif // WINDOW_H
