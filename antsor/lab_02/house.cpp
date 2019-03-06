#include "house.h"

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


House::House()
{
	pos.setX(0);
	pos.setY(0);
	
	base.setTopLeft(pos.x(), pos.y() + ROOF_H);
	base.setBottomRight(pos.x() + BASE_W, pos.y() + ROOF_H + BASE_H);
	base.setAngle(0);
	
	roof.point(0)->setX(pos.x());
	roof.point(0)->setY(pos.y() + ROOF_H);
	
	roof.point(1)->setX(pos.x() + ROOF_PEAK_X);
	roof.point(1)->setY(pos.y());
	
	roof.point(2)->setX(pos.x() + BASE_W);
	roof.point(2)->setY(pos.y() + ROOF_H);
	
	roof_window.setCenter(pos.x() + ROOF_WINDOW_X, pos.y() + ROOF_WINDOW_Y);
	roof_window.setA(ROOF_WINDOW_R);
	roof_window.setB(ROOF_WINDOW_R);
	roof_window.setAngle(0);
	
	bwindow1_arc.setCenter(pos.x() + WINDOW1_X + WINDOW1_W / 2,
						   pos.y() + WINDOW1_Y + WINDOW1_ARC_H);
	roof_window.setA(WINDOW1_W / 2);
	roof_window.setB(WINDOW1_ARC_H);
	roof_window.setAngle(0);
	
	bwindow1_rect.setTopLeft(pos.x() + WINDOW1_X,
							 pos.y() + WINDOW1_Y + WINDOW1_ARC_H);
	bwindow1_rect.setBottomRight(pos.x() + WINDOW1_X + WINDOW1_W,
								 pos.y() + WINDOW1_Y + WINDOW1_H);
	bwindow1_rect.setAngle(0);
	
	bwindow1_line.p1()->setX(pos.x() + WINDOW1_X + WINDOW1_W / 2);
	bwindow1_line.p1()->setY(pos.y() + WINDOW1_Y + WINDOW1_ARC_H);
	bwindow1_line.p2()->setX(pos.x() + WINDOW1_X + WINDOW1_W / 2);
	bwindow1_line.p1()->setY(pos.y() + WINDOW1_Y + WINDOW1_H);
	
	bwindow2.setCenter(pos.x() + WINDOW2_X, pos.y() + WINDOW2_Y);
	bwindow2.setA(WINDOW1_W / 2);
	bwindow2.setB(WINDOW1_H / 2);
	bwindow2.setAngle(0);
	
	bwindow2_d1.p1()->setX(pos.x() + WINDOW2_X + WINDOW2_W / 2);
	bwindow2_d1.p1()->setY(pos.y() + WINDOW2_Y);
	bwindow2_d1.p2()->setX(pos.x() + WINDOW2_X + WINDOW2_W / 2);
	bwindow2_d1.p2()->setY(pos.y() + WINDOW2_Y + WINDOW2_H);
	
	bwindow2_d2.p1()->setX(pos.x() + WINDOW2_X);
	bwindow2_d2.p1()->setY(pos.y() + WINDOW2_Y + WINDOW2_H / 2);
	bwindow2_d2.p2()->setX(pos.x() + WINDOW2_X + WINDOW2_W);
	bwindow2_d2.p2()->setY(pos.y() + WINDOW2_Y + WINDOW2_H / 2);
}
