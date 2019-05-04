#include <QApplication>
#include <cmath>

#include "fill.h"

ColorSet::ColorSet(QColor cedge, QColor cfill, QColor cbg) :
	color_edge(cedge),
	color_fill(cfill),
	color_bg(cbg)
{
	
}

Point lt_corner(std::vector<Polygon> set)
{
	if (set.size() == 0 || set[0].number_of_vertexes() == 0)
		return Point();
	
	int xmin = set[0][0].x();
	int ymin = set[0][0].y();
	
	for (size_t i = 0; i < set.size(); i++)
		for (int j = 0; j < set[i].number_of_vertexes(); j++)
		{
			
			if (set[i][j].x() < xmin)
				xmin = set[i][j].x();
			if (set[i][j].y() < ymin)
				ymin = set[i][j].y();
		}
	return Point(xmin, ymin);
}

Point rd_corner(std::vector<Polygon> set)
{
	if (set.size() == 0 || set[0].number_of_vertexes() == 0)
		return Point();
	
	int xmax = set[0][0].x();
	int ymax = set[0][0].y();
	
	for (size_t i = 0; i < set.size(); i++)
		for (int j = 0; j < set[i].number_of_vertexes(); j++)
		{
			
			if (set[i][j].x() > xmax)
				xmax = set[i][j].x();
			if (set[i][j].y() > ymax)
				ymax = set[i][j].y();
		}
	return Point(xmax, ymax);
}

void fill(QImage *img, ColorSet color_set, std::vector<Edge> edges,
		  QGraphicsScene *scene, int line_x, int delay)
{
	if (!img || edges.size() == 0)
		return;
	
	for (size_t i = 0; i < edges.size(); i++)
		if (!edges[i].is_horizontal())
		{
			int top_y = edges[i].p1()->y();
			int bottom_y = edges[i].p2()->y();
			int left_x = edges[i].p1()->x();
			int right_x = edges[i].p2()->x();
			
			if (top_y > bottom_y)
			{
				top_y = edges[i].p2()->y();
				bottom_y = edges[i].p1()->y();
				left_x = edges[i].p2()->x();
				right_x = edges[i].p1()->x();
			}
			
			float dx = (float)(right_x - left_x) / (bottom_y - top_y);
			float edge_x = left_x;
			for (int y = top_y; y < bottom_y; y++, edge_x += dx)
			{
				float start_x = edge_x + 1, end_x = line_x;
				if (line_x < edge_x)
				{
					start_x = line_x;
					end_x = edge_x;
				}
				for (int x = round(start_x); x < end_x; x++)
				{
					QColor color = img->pixelColor(x, y);
					QColor color_draw = color_set.color_edge;
					if (color == color_set.color_fill)
						color_draw = color_set.color_bg;
					else if (color == color_set.color_bg)
						color_draw = color_set.color_fill;
					if (color != color_set.color_edge)
						img->setPixelColor(x, y, color_draw);
				}
				
				if (delay > 0)
				{
					scene->addPixmap(QPixmap::fromImage(*img));
					QApplication::processEvents(QEventLoop::AllEvents, 1);
				}
			}
		}
	
	if (delay == 0)
		scene->addPixmap(QPixmap::fromImage(*img));
}
