#include <cmath>

#include "clipper.h"

Clipper::Clipper(int x1, int y1, int x2, int y2)
{
	left = x1;
	top = y1;
	right = x2;
	bottom = y2;
}

void Clipper::clip(std::vector<LineSeg>& lines, Painter& painter)
{
	for (size_t i = 0; i < lines.size(); i++)
		clipLineSeg(lines[i], painter);
}

void Clipper::clipLineSeg(LineSeg& line, Painter& painter)
{
	/// Cohen-Sutherland
	/// 
	Point p1 = line.getSource();
	Point p2 = line.getPurpose();
	
	
	PosState pos = COMMON;			// 0
    double m = 1;

    if (line.isVertical())
        pos = VERTICAL;				// -1
	else if (line.isHorizontal())
	{
		pos = HORIZONTAL;			// 1
		m = 0;
	}
	else
		m = double(p2.y() - p1.y()) / (p2.x() - p1.x());
	
	unsigned masks[] = { codeMasks.outOfLeft, codeMasks.outOfRight,
					   codeMasks.outOfBottom, codeMasks.outOfTop };
	
	int clipCoords[] = { left, right, bottom, top };
	
    for (int i = 0; i < 4; i++)
	{
		Visibility vis = isVisible(p1, p2);
		if (vis == INVISIBLE)
			return;
		if (vis == VISIBLE)
		{
			painter.drawClipped(p1.x(), p1.y(), p2.x(), p2.y());
			return;
		}
		
		unsigned code1 = getCode(p1) & masks[i];
		unsigned code2 = getCode(p2) & masks[i];

        if (code1 == code2)
            continue;

        if (code1 == 0)
		{
			Point tmp = p1;
			p1 = p2;
			p2 = tmp;
		}

        if (pos != VERTICAL && i < 2)
		{
			p1.setY(round(m * (clipCoords[i] - p1.x())) + p1.y());
			p1.setX(clipCoords[i]);
		}
		else
		{
			if (pos != VERTICAL)
				p1.setX(round((1 / m) * (clipCoords[i] - p1.y())) + p1.x());
			p1.setY(clipCoords[i]);
		}
	}
	
    painter.drawClipped(p1.x(), p1.y(), p2.x(), p2.y());
}

unsigned Clipper::getCode(Point &p)
{
	unsigned code = 0;
	if (p.x() < left)
		code |= codeMasks.outOfLeft;
	if (p.x() > right)
		code |= codeMasks.outOfRight;
	if (p.y() < top)
		code |= codeMasks.outOfTop;
	if (p.y() > bottom)
		code |= codeMasks.outOfBottom;
	return code;
}

Clipper::Visibility Clipper::isVisible(Point p1, Point p2)
{
	unsigned code1 = getCode(p1);
	unsigned code2 = getCode(p2);

    if (code1 == 0 && code2 == 0)
	{
        return VISIBLE;
	}

	unsigned lcode = code1 & code2;
	if (lcode != 0)
		return INVISIBLE;

	return PART_VISIBLE;
}
