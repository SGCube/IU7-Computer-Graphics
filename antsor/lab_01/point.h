#ifndef POINT_H
#define POINT_H


class Point
{
public:
	Point();
	Point(float x, float y);
	
	float x();
	float y();
	void setX(float x);
	void setY(float y);
	
private:
	float xcoord;
	float ycoord;
};

float dist(Point p1, Point p2);

#endif // POINT_H
