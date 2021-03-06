#include "house.h"

House::House(Point pos = Point(0, 0))
	: base(pos, BASE_W, BASE_H),
	  roof(pos, Point(pos.x() + ROOF_PEAK_X, pos.y() - ROOF_H),
		   Point(pos.x() + BASE_W, pos.y())),
	  roof_window(Point(pos.x() + ROOF_WINDOW_X, pos.y() - ROOF_WINDOW_Y),
				  ROOF_WINDOW_R, ROOF_WINDOW_R),
	  base_window1(Point(pos.x() + WINDOW1_X,
						 pos.y() + WINDOW1_Y + WINDOW1_ARC_H),
				   WINDOW1_W, WINDOW1_H),
	  base_window1_arc(Point(pos.x() + WINDOW1_X + WINDOW1_W / 2,
							 pos.y() + WINDOW1_Y + WINDOW1_ARC_H),
					   WINDOW1_W / 2, WINDOW1_ARC_H, -180),
	  base_window1_line(Point(pos.x() + WINDOW1_X + WINDOW1_W / 2,
							  pos.y() + WINDOW1_Y),
						Point(pos.x() + WINDOW1_X + WINDOW1_W / 2,
							  pos.y() + WINDOW1_Y + WINDOW1_H + WINDOW1_ARC_H)),
	  base_window2(Point(pos.x() + WINDOW2_X + WINDOW2_W / 2,
						 pos.y() + WINDOW2_Y + WINDOW2_H / 2),
				   WINDOW2_W / 2, WINDOW2_H / 2),
	  base_window2_linev(Point(pos.x() + WINDOW2_X + WINDOW2_W / 2,
							   pos.y() + WINDOW2_Y),
						 Point(pos.x() + WINDOW2_X + WINDOW2_W / 2,
							   pos.y() + WINDOW2_Y + WINDOW2_H)),
	  base_window2_lineh(Point(pos.x() + WINDOW2_X,
							   pos.y() + WINDOW2_Y + WINDOW2_H / 2),
						 Point(pos.x() + WINDOW2_X + WINDOW2_W,
							   pos.y() + WINDOW2_Y + WINDOW2_H / 2))
{
	
}

void House::move(int dx, int dy)
{
	base.move(dx, dy);
	roof.move(dx, dy);
	roof_window.move(dx, dy);
	base_window1.move(dx, dy);
	base_window1_line.move(dx, dy);
	base_window1_arc.move(dx, dy);
	base_window2.move(dx, dy);
	base_window2_linev.move(dx, dy);
	base_window2_lineh.move(dx, dy);
}

void House::scale(double kx, double ky, Point pm)
{
	base.scale(kx, ky, pm);
	roof.scale(kx, ky, pm);
	roof_window.scale(kx, ky, pm);
	base_window1.scale(kx, ky, pm);
	base_window1_line.scale(kx, ky, pm);
	base_window1_arc.scale(kx, ky, pm);
	base_window2.scale(kx, ky, pm);
	base_window2_linev.scale(kx, ky, pm);
	base_window2_lineh.scale(kx, ky, pm);
}

void House::rotate(int deg, Point pc)
{
	base.rotate(deg, pc);
	roof.rotate(deg, pc);
	roof_window.rotate(deg, pc);
	base_window1.rotate(deg, pc);
	base_window1_line.rotate(deg, pc);
	base_window1_arc.rotate(deg, pc);
	base_window2.rotate(deg, pc);
	base_window2_linev.rotate(deg, pc);
	base_window2_lineh.rotate(deg, pc);
}

void House::draw(QGraphicsScene *scene)
{
	scene->clear();
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
