#ifndef POINTDATA_H
#define POINTDATA_H

#include "point.h"

class PointData
{
public:
	PointData(Point p, PointData* prevPoint=nullptr, PointData* nextPoint=nullptr) :
		point_(p), prev_(prevPoint), next_(nextPoint) {}
	
	Point& data() { return point_; }
	PointData*& prev() { return prev_; }
	PointData*& next() { return next_; }
	
private:
	Point point_;
	PointData* prev_;
	PointData* next_;
};

class IntersectData : PointData
{
public:
	IntersectData(Point p, PointData* link, PointData* prevPoint=nullptr,
				  PointData* nextPoint=nullptr) :
		PointData(p, prevPoint, nextPoint), link_(link) {}
	
	PointData*& link() { return link_; }
	
private:
	PointData* link_;
};

class PointDataList
{
public:
	PointDataList(): head_(nullptr), tail_(nullptr), cur_(nullptr) {}
	~PointDataList();
	
	void insert(PointData* p, PointData* after);
	void push_back(PointData* p);
	void push_front(PointData* p);
	
	Point pop_front();
	Point pop_back();
	
	PointData* head();
	PointData* tail();
	PointData* cur();
	PointData* prev();
	PointData* next();
	
private:
	PointData* head_;
	PointData* tail_;
	PointData* cur_;
};

#endif // POINTDATA_H
