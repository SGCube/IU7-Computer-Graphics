#include "house.h"

House::House(Point start_pos)
{
	pos.setX(start_pos.x());
	pos.setY(start_pos.y());
	
	base = Rectangle(pos, BASE_W, BASE_H);
	
	roof = Triangle(pos, Point(pos.x() + ROOF_PEAK_X, pos.y() - ROOF_H),
					Point(pos.x() + BASE_W, pos.y()));
	
	roof_window = Ellipse(Point(ROOF_WINDOW_X, pos.y() - ROOF_WINDOW_Y),
						  ROOF_WINDOW_R, ROOF_WINDOW_R);
	
	base_window1 = Rectangle(Point(WINDOW1_X, WINDOW1_Y + WINDOW1_ARC_H),
							 WINDOW1_W, WINDOW1_H);
	
	base_window1_arc = Arc(Point(WINDOW1_X + WINDOW1_W / 2,
								 WINDOW1_Y + WINDOW1_ARC_H),
						   WINDOW1_W / 2, WINDOW1_ARC_H);
	
	base_window1_line = LineSeg(Point(WINDOW1_X + WINDOW1_W / 2, WINDOW1_Y),
								Point(WINDOW1_X + WINDOW1_W / 2,
									  WINDOW1_Y + WINDOW1_H + WINDOW1_ARC_H));
	
	base_window2 = Ellipse(Point(WINDOW2_X + WINDOW2_W / 2,
								 WINDOW2_Y + WINDOW2_H / 2),
						   WINDOW2_W / 2, WINDOW2_H / 2);
	
	base_window2_linev = LineSeg(Point(WINDOW2_X + WINDOW2_W / 2, WINDOW2_Y),
								 Point(WINDOW2_X + WINDOW2_W / 2,
									   WINDOW2_Y + WINDOW2_H));
	
	base_window2_lineh = LineSeg(Point(WINDOW2_X, WINDOW2_Y + WINDOW2_H / 2),
								 Point(WINDOW2_X + WINDOW2_W,
									   WINDOW2_Y + WINDOW2_H / 2));
}

void House::draw(QGraphicsScene *scene)
{
	base.draw(scene);
	roof.draw(scene);
	roof_window.draw(scene);
	base_window1.draw(scene);
	base_window1_line.draw(scene);
	base_window1_arc.draw(scene);
	base_window2.draw(scene);
	base_window2_linev.draw(scene);
	base_window2_lineh.draw(scene);
}
