#ifndef POINT_H
#define POINT_H

class Point
{
public:
	Point();
	Point(double x, double y);
	
	double x();
	double y();
	void setX(double x);
	void setY(double y);
	
private:
	double xcoord;
	double ycoord;
};

double dist(Point p1, Point p2);

#endif // POINT_H
