#include <QApplication>
#include <cmath>
#include <vector>

#include "fill.h"

ColorSet::ColorSet(QColor cedge, QColor cfill, QColor cbg) :
	color_edge(cedge),
	color_fill(cfill),
	color_bg(cbg)
{
	
}

void search_seed(QImage *img, ColorSet color_set, std::vector<Point> *stack,
				  int xleft, int xright, int ystr)
{
	bool flag = false;
	int x = xleft, y = ystr;
	int xtmp = x;
	while (x <= xright)
	{
		flag = false;
		while (img->pixelColor(x, y) != color_set.color_edge && 
			   img->pixelColor(x, y) != color_set.color_fill && x <= xright)
		{
			if (!flag)
				flag = true;
			x++;
		}

		if (flag)
		{
			if (x == xright &&
				img->pixelColor(x, y) != color_set.color_fill &&
				img->pixelColor(x, y) != color_set.color_edge)
				stack->push_back(Point(x, y));
			else
				stack->push_back(Point(x - 1, y));
			flag = false;
		}

		xtmp = x;
		while ((img->pixelColor(x, y) == color_set.color_edge ||
			   img->pixelColor(x, y) == color_set.color_fill) && 
			   x < xright)
			x++;
		
		if (x == xtmp)
			x++;
	}
}

void fill(QImage *img, ColorSet color_set, QGraphicsScene *scene, Point seed,
		  int delay)
{
	if (!img || !scene)
		return;
	
	std::vector<Point> stack;
	stack.push_back(seed);

	while (!stack.empty())
	{
		Point p = stack.back();
		stack.pop_back();
		
		int x = p.x(), y = p.y();
		int xtmp = p.x();
		bool flag = false;
		
		img->setPixelColor(x, y, color_set.color_fill);
		
		// заполнение слева от затравки
		x--;
		while (img->pixelColor(x, y) != color_set.color_edge)
		{
			img->setPixelColor(x, y, color_set.color_fill);
			x--;
		}
		int xleft = x + 1;
		
		// заполнение справа от затравки
		x = xtmp;
		x++;
		while (img->pixelColor(x, y) != color_set.color_edge)
		{
			img->setPixelColor(x, y, color_set.color_fill);
			x++;
		}
		int xright = x - 1;
		
		// поиск затравки на строке выше
		search_seed(img, color_set, &stack, xleft, xright, y - 1);

		// поиск затравки на строке ниже
		search_seed(img, color_set, &stack, xleft, xright, y + 1);

		if (delay > 0)
		{
			scene->addPixmap(QPixmap::fromImage(*img));
			QApplication::processEvents(QEventLoop::AllEvents, 1);
		}
	}

	if (delay == 0)
		scene->addPixmap(QPixmap::fromImage(*img));
}
