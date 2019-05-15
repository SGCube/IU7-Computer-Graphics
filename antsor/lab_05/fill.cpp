#include <QApplication>
#include <QTime>
#include <cmath>
#include "fill.h"

ColorSet::ColorSet(QColor cedge, QColor cfill, QColor cbg) :
	color_edge(cedge),
	color_fill(cfill),
	color_bg(cbg)
{
	
}

Point lt_corner(std::vector<Polygon> &set)
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

Point rd_corner(std::vector<Polygon> &set)
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

int divline_x(std::vector<Polygon> &set)
{
	if (set.size() == 0 || set[0].number_of_vertexes() == 0)
		return -1;
	
	Point lt_point = lt_corner(set);
	Point rd_point = rd_corner(set);
	
	int middle_x = (rd_point.x() + lt_point.x()) / 2;
	int min_dist = middle_x - lt_point.x();
	int cur_dist = 0;
	int line_x = -1;
	
	for (size_t i = 0; i < set.size(); i++)
		for (int j = 0; j < set[i].number_of_vertexes(); j++)
		{
			cur_dist = abs(set[i][j].x() - middle_x);
			if (cur_dist < min_dist)
			{
				min_dist = cur_dist;
				line_x = set[i][j].x();
			}
		}
	return line_x;
}

void fill(QImage *img, ColorSet color_set, std::vector<Edge> edges,
		  QGraphicsScene *scene, int line_x, int delay)
{
	if (!img || edges.size() == 0)
		return;
	
	QColor pixel_color = color_set.color_edge;
	QColor draw_color = color_set.color_edge;
	
	for (size_t i = 0; i < edges.size(); i++)
	{
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
					pixel_color = img->pixelColor(x, y);
					if (pixel_color == color_set.color_fill)
						draw_color = color_set.color_bg;
					else
						draw_color = color_set.color_fill;
					img->setPixelColor(x, y, draw_color);
				}
				
				if (delay > 0)
				{
					scene->addPixmap(QPixmap::fromImage(*img));
					QTime dieTime = QTime::currentTime().addMSecs(delay);
					while(QTime::currentTime() < dieTime)
						QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
				}
			}
		}
	}
	
	if (delay == 0)
		scene->addPixmap(QPixmap::fromImage(*img));
}
