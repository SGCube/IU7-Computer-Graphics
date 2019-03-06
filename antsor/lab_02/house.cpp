#include "house.h"

#define BASE_W 100
#define BASE_H 100

#define WINDOW1_W 50
#define WINDOW1_H 50
#define WINDOW1_X 10
#define WINDOW1_Y 10
#define WINDOW1_ARC_H 10

#define WINDOW2_W 20
#define WINDOW2_H (WINDOW1_H)
#define WINDOW2_X (WINDOW1_X + WINDOW1_H + 10)
#define WINDOW2_Y (WINDOW1_Y)

#define ROOF_H 40
#define ROOF_PEAK_X 30
#define ROOF_WINDOW_X (ROOF_PEAK_X + 10)
#define ROOF_WINDOW_Y (ROOF_H / 2)
#define ROOF_WINDOW_R 10

House::House()
{
	base.set
			
	Rectangle base;
	Triangle roof;
	Ellipse roof_window;
	
	Ellipse bwindow1_arc;
	Rectangle bwindow1_rect;
	LineSeg bwindow1_line;
	
	Ellipse bwindow2;
	LineSeg bwindow2_d1;
	LineSeg bwindow2_d2;
}
