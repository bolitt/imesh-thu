#include "predefs.h"

vector<triangle *> triangleList;
edgefront edfr;
deque<edge *> frontEdgeQueue;

void grid::initialize()
{
	long indexbound = pointsdatabase->points.size();
	for(long count = 0; count < indexbound;count++)
	{
		int _i = min(isize-1,(int)(floor(pointsdatabase->points[count].position.x / gridwidth)+0.1));//all point must have non-negative position values
		int _j = min(jsize-1,(int)(floor(pointsdatabase->points[count].position.y / gridwidth)+0.1));
		int _k = min(ksize-1,(int)(floor(pointsdatabase->points[count].position.z / gridwidth)+0.1));

		cells.at(_k).at(_i).at(_j).add_pointindex(count);
	}
	printf("point1 OK");
	//for(int k = 0;k < ksize; k++)
	//	for(int i = 0; i < isize; i++)
	//		for(int j = 0; j < jsize; j++)
	//			cells.at(k).at(i).at(j).bucket_sort(0,cells.at(k).at(i).at(j).pointindex.size()-1);
}

void cell::add_pointindex(long _pointindex)
{
	this->pointindex.push_back(_pointindex);
	this->pointnum += 1;

}

void cell::bucket_sort(int startindex, int endindex)
{
	if(startindex >= endindex)
		return;
	if(startindex < 0 || endindex >= this->pointindex.size())
		return;

	int low = startindex;
	int high = endindex;

	point *pivot = &(pointsdatabase->points.at(pointindex.at(low)));

	while(low<high)
	{
		while(low < high && point::comparePoint(*pivot, pointsdatabase->points.at(pointindex.at(high))) == false)
			high--;
		if(low<high)
		{
			long temp = pointindex.at(high);
			pointindex[high] = pointindex[low];
			pointindex[low] = temp;
		}
		while(low < high && point::comparePoint(*pivot, pointsdatabase->points.at(pointindex.at(low))) == true)
			low++;
		if(low<high)
		{
			long temp = pointindex.at(low);
			pointindex[low] = pointindex[high];
			pointindex[high] = temp;
		}
	}
	bucket_sort(startindex,low-1);
	bucket_sort(low,endindex);

}

//static bool point::comparePoint(point a, point b)
//{
//	if(a.x == b.x)
//		if(a.y == b.y)
//			return a.z > b.z;
//		else
//			return a.y > b.y;
//	else
//		return a.x > b.x;
//}
//
void grid::locateNeighborhood(std::vector<int3> &neighbors,int cellindex)
{
	neighbors.clear();
	if(cellindex>=isize*jsize*ksize||cellindex<0)
		return;

	int temp = cellindex;
	int cellk = temp/(isize*jsize);

	temp = temp-cellk*isize*jsize;
	int celli = temp/jsize;
	int cellj = temp-celli*jsize;

	neighbors.push_back(int3(celli,cellj,cellk));
	if(cellk != ksize-1)
		neighbors.push_back(int3(celli,cellj,cellk+1));
	if(cellk != 0)
		neighbors.push_back(int3(celli,cellj,cellk-1));
	if(cellj != jsize-1)
	{
		neighbors.push_back(int3(celli,cellj+1,cellk));
		if(cellk != 0)
			neighbors.push_back(int3(celli,cellj+1,cellk-1));
		if(cellk != ksize-1)
			neighbors.push_back(int3(celli,cellj+1,cellk+1));
	}
	if(cellj != 0)
	{
		neighbors.push_back(int3(celli,cellj-1,cellk));
		if(cellk != 0)
			neighbors.push_back(int3(celli,cellj-1,cellk-1));
		if(cellk != ksize-1)
			neighbors.push_back(int3(celli,cellj-1,cellk+1));
	}
	if(celli != 0)
	{
		neighbors.push_back(int3(celli-1,cellj,cellk));
		if(cellj != 0)
		{
			neighbors.push_back(int3(celli-1,cellj-1,cellk));
			if(cellk != 0)
				neighbors.push_back(int3(celli-1,cellj-1,cellk-1));
			if(cellk != ksize-1)
				neighbors.push_back(int3(celli-1,cellj-1,cellk+1));
		}

		if(cellk != 0)
			neighbors.push_back(int3(celli-1,cellj,cellk-1));
		if(cellj != jsize-1)
		{
			neighbors.push_back(int3(celli-1,cellj+1,cellk));
			if(cellk != 0)
				neighbors.push_back(int3(celli-1,cellj+1,cellk-1));
			if(cellk != ksize-1)
				neighbors.push_back(int3(celli-1,cellj+1,cellk+1));
		}
		if(cellk != ksize-1)
			neighbors.push_back(int3(celli-1,cellj,cellk+1));
	}
	if(celli != isize-1)
	{
		neighbors.push_back(int3(celli+1,cellj,cellk));
		if(cellj != 0)
		{
			neighbors.push_back(int3(celli+1,cellj-1,cellk));
			if(cellk != 0)
				neighbors.push_back(int3(celli+1,cellj-1,cellk-1));
			if(cellk != ksize-1)
				neighbors.push_back(int3(celli+1,cellj-1,cellk+1));
		}

		if(cellk != 0)
			neighbors.push_back(int3(celli+1,cellj,cellk-1));
		if(cellj != jsize-1)
		{
			neighbors.push_back(int3(celli+1,cellj+1,cellk));
			if(cellk != 0)
				neighbors.push_back(int3(celli+1,cellj+1,cellk-1));
			if(cellk != ksize-1)
				neighbors.push_back(int3(celli+1,cellj+1,cellk+1));
		}
		if(cellk != ksize-1)
			neighbors.push_back(int3(celli+1,cellj,cellk+1));
	}
}

bool grid::pickPointInCell(long &_index, int _cellindex)
{
	if(_cellindex>=isize*jsize*ksize||_cellindex<0)
		return false;

	int temp = _cellindex;
	int cellk = temp/(isize*jsize);

	temp = temp-cellk*isize*jsize;
	int celli = temp/jsize;
	int cellj = temp-celli*jsize;

	cell *c = &(cells.at(cellk).at(celli).at(cellj));

	if(c->activated || c->currentpointindex >= c->pointnum)
		return false;

	while(this->getPoint(c->pointindex[c->currentpointindex]).flag != point::UNUSED && c->currentpointindex < c->pointnum)
		c->currentpointindex += 1;
	if(c->currentpointindex >= c->pointnum)
		return false;

	_index = c->pointindex[c->currentpointindex];
	c->currentpointindex += 1;

	return true;
}

void grid::locatePoint(point3D pos, int3 &_cellindex)
{
	_cellindex.first = floor(pos.x/gridwidth)+0.1;
	_cellindex.second = floor(pos.y/gridwidth)+0.1;
	_cellindex.third = floor(pos.z/gridwidth)+0.1;
}

void grid::locatePoint(long _index,int3 &_cellindex)
{
	point3D pos = this->pointsdatabase->points[_index].position;
	locatePoint(pos,_cellindex);
}

void grid::findNeighborPoints(vector<long> &pointList, double radius, point3D &origin)
{
	int3 cell0;
	locatePoint(origin,cell0);

	for(int i = cell0.first-1;i<=cell0.first+1;i++)
		for(int j = cell0.second-1;j <=cell0.second+1;j++)
			for(int k = cell0.third-1;k <=cell0.third+1;k++)
			{
				if(!this->inGrid(int3(i,j,k)))
					continue;

				int currentnum = cells.at(k).at(i).at(j).pointnum;
				for(int count = 0;count <currentnum;count++)
				{
					long cpointindex = cells.at(k).at(i).at(j).pointindex[count];
					point3D cpoint = this->pointsdatabase->points[cpointindex].position;

					if(point3D::distance2(cpoint,origin)<4*radius*radius)
						pointList.push_back(cpointindex);
				}
			}
}

				