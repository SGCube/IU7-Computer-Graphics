#include <QApplication>
#include <QTime>
#include <cmath>
#include <vector>

#include "fill.h"

ColorSet::ColorSet(QColor cedge, QColor cfill, QColor cbg) :
	color_edge(cedge),
	color_fill(cfill),
	color_bg(cbg)
{
	
}

void search_span(QImage *img, ColorSet color_set, std::list<Point> *stack,
				  int xleft, int xright, int ystr)
{
	if (ystr < 0 || ystr >= img->height())
		return;
	
	bool flag = false;
	int x = xleft, y = ystr;
	int xtmp = x;
	while (x <= xright)
	{
		flag = false;
		while (x <= xright && img->pixelColor(x, y) != color_set.color_edge && 
			   img->pixelColor(x, y) != color_set.color_fill)
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
		while (x < xright && (img->pixelColor(x, y) == color_set.color_edge ||
			   img->pixelColor(x, y) == color_set.color_fill))
			x++;
		
		if (x == xtmp)
			x++;
	}
}

void fill(QImage *img, ColorSet color_set, Canvas *canvas, Point span,
		  int delay)
{
	if (!img || !canvas)
		return;
	
	std::list<Point> stack;
	stack.push_back(span);

	while (!stack.empty())
	{
		Point p = stack.back();
		stack.pop_back();
		
		int x = p.x(), y = p.y();
		int xtmp = p.x();
		
		img->setPixelColor(x, y, color_set.color_fill);
		
		// заполнение слева от затравки
		x--;
		while (x >= 0 && img->pixelColor(x, y) != color_set.color_edge)
		{
			img->setPixelColor(x, y, color_set.color_fill);
			x--;
		}
		int xleft = x + 1;
		
		// заполнение справа от затравки
		x = xtmp;
		x++;
		while (x < img->width() && img->pixelColor(x, y) != color_set.color_edge)
		{
			img->setPixelColor(x, y, color_set.color_fill);
			x++;
		}
		int xright = x - 1;
		
		// поиск затравки на строке ниже
		search_span(img, color_set, &stack, xleft, xright, y + 1);

		// поиск затравки на строке выше
		search_span(img, color_set, &stack, xleft, xright, y - 1);

		if (delay > 0)
		{
			canvas->repaint();
			QTime dieTime = QTime::currentTime().addMSecs(delay);
			while(QTime::currentTime() < dieTime)
				QCoreApplication::processEvents(QEventLoop::AllEvents, delay);
		}
	}

	if (delay == 0)
		canvas->repaint();
}
