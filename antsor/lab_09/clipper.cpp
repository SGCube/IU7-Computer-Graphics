#include <cmath>

#include "clipper.h"
#include "vector.hpp"
#include "pointdata.h"

void Clipper::clip(std::vector<Polygon> &polygons, Painter &painter)
{
	std::vector<PointDataList> pLists;
	std::vector<PointDataList> cLists;
	
	for (size_t i = 0; i < polygons.size(); i++)
	{
		PointDataList pList;
		for (size_t j = 0; j < polygons.size(); j++)
		{
			PointData* data = new PointData(polygons[i][j]);
			pList.push_back(data);
		}
		pLists.push_back(pList);
	}
	
	for (size_t i = 0; i < clippers.size(); i++)
	{
		PointDataList cList;
		for (size_t j = 0; j < clippers.size(); j++)
		{
			PointData* data = new PointData(clippers[i][j]);
			cList.push_back(data);
		}
		cLists.push_back(cList);
	}
	
	
	
	pLists.clear();
	cLists.clear();
}
