#ifndef HOUSE_H
#define HOUSE_H

#include "lineseg.h"
#include "rectangle.h"
#include "ellipse.h"
#include "triangle.h"
#include "arc.h"
#include "outline.h"

#define POINTS_N 1000

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
#define WINDOW2_X (WINDOW1_X + WINDOW1_H + 10)
#define WINDOW2_Y (WINDOW1_Y)

#define START_X 300
#define START_Y 300

class House
{
public:
	House();
	
private:
	Point pos;
	
	Rectangle base;						// корпус дома
	Point roof_peak_pos;				// позиция вершины крыши
	Ellipse roof_window;				// окно крышы
	
	Arc base_window1_arc;				// дуга левого окна корпуса
	LineSeg base_window1_line;			// "линия" левого окна корпуса
	Rectangle base_window1_rect;		// основа левого окна корпуса
	
	Ellipse base_window2;				// правое окно корпуса
	LineSeg base_window2_lines[2];		// "линии" правого окна корпуса
	
	/*
	Point base[4];						// корпус дома
	Point roof_peak_pos;				// позиция вершины крыши
	
	Point roof_window[4 * POINTS_N];	// окно крышы
	
	Point base_window1_arc[POINTS_N];	// дуга левого окна корпуса
	Point base_window1_line[2];			// "линия" левого окна корпуса
	Point base_window1_rect[4];			// основа левого окна корпуса
	
	Point base_window2[4 * POINTS_N];	// правое окно корпуса
	Point base_window2_linev[2];		// "линии" правого окна корпуса
	Point base_window2_lineh[2];		// "линии" правого окна корпуса
	*/
	
	/*
	Outline base;						// корпус дома
	Outline roof;						// крыша дома
	
	Outline roof_window;				// окно крышы
	
	Outline base_window1_arc;			// дуга левого окна корпуса
	Outline base_window1_line;			// "линия" левого окна корпуса
	Outline base_window1_rect;			// основа левого окна корпуса
	
	Outline base_window2;				// правое окно корпуса
	Outline base_window2_linev;			// "линии" правого окна корпуса
	Outline base_window2_lineh;			// "линии" правого окна корпуса
	*/
};

#endif // HOUSE_H
