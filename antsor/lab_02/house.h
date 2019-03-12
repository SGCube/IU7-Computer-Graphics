#ifndef HOUSE_H
#define HOUSE_H

#include "lineseg.h"
#include "rectangle.h"
#include "ellipse.h"
#include "triangle.h"
#include "arc.h"

#define BASE_W 100
#define BASE_H 100

#define ROOF_H 40
#define ROOF_PEAK_X 30
#define ROOF_WINDOW_X (ROOF_PEAK_X + 10)
#define ROOF_WINDOW_Y (ROOF_H / 2)
#define ROOF_WINDOW_R 10

#define WINDOW1_W 50
#define WINDOW1_H 50
#define WINDOW1_X 10
#define WINDOW1_Y (ROOF_H + 10)
#define WINDOW1_ARC_H 10

#define WINDOW2_W 20
#define WINDOW2_H (WINDOW1_H)
#define WINDOW2_X (WINDOW1_X + WINDOW1_W + 10)
#define WINDOW2_Y (WINDOW1_Y)

#define START_X 300
#define START_Y 300

class House
{
public:
	House(Point pos);
	
	void draw(QGraphicsScene *scene);
	
private:
	Rectangle base;						// корпус дома
	Triangle roof;						// крыша дома
	Ellipse roof_window;				// окно крышы
	
	Rectangle base_window1;				// основа левого окна корпуса
	Arc base_window1_arc;				// дуга левого окна корпуса
	LineSeg base_window1_line;			// "линия" левого окна корпуса
	
	Ellipse base_window2;				// основа правого окна корпуса
	LineSeg base_window2_linev;			// "линии" правого окна корпуса
	LineSeg base_window2_lineh;			// "линии" правого окна корпуса
};

#endif // HOUSE_H
