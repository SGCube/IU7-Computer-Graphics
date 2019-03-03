#ifndef POINT_H
#define POINT_H


class Point
{
public:
	Point();
	Point(float px, float py);
	
	float getX();
	float getY();
	void setX(float px);
	void setY(float py);
	
private:
	float x;
	float y;
};

float dist(Point p1, Point p2);

#endif // POINT_H
