#include "SeedSelection.h"

bool findSeedTriangle(grid *m_grid, long &_pointindex1, long &_pointindex2, long &_pointindex3, point3D &ball_center, double ball_radius, TriangulationHandler *TH)
{
	bool found = false;
	int gridsize = m_grid->isize*m_grid->jsize*m_grid->ksize;
	vector<int3> neighborhood;

	do
	{
		long pointindex1;
		while(m_grid->currentcellindex<gridsize && !m_grid->pickPointInCell(pointindex1,m_grid->currentcellindex))
			m_grid->currentcellindex += 1;

		printf("\n%d",m_grid->currentcellindex);
		if(m_grid->currentcellindex >= gridsize)
		{
			break;
		}

		m_grid->locateNeighborhood(neighborhood,m_grid->currentcellindex);

		int i = 0,j = 0,k = 0;
		long pointindex2;
		long pointindex3;
		int iupbound,jupbound,jupbound1;
		bool t_valid = false;
		iupbound = neighborhood.size();

		while(found == false && i < iupbound)
		{
			j = 0;
			int3 current = neighborhood[i];
			jupbound = m_grid->cells.at(current.third).at(current.first).at(current.second).pointnum;

			while(found == false && j < jupbound)
			{
				pointindex2 = m_grid->cells.at(current.third).at(current.first).at(current.second).pointindex[j];
				if(!(m_grid->getPoint(pointindex2).isUnused()))
				{
					j++;
					continue;
				}

				for(int i1 = 0;i1 < iupbound;i1++)
				{
					int3 current1 = neighborhood[i1];
					jupbound1 = m_grid->cells.at(current1.third).at(current1.first).at(current1.second).pointnum;
					for(int j1 = 0;j1 < jupbound1; j1++)
					{
						pointindex3 = m_grid->cells.at(current1.third).at(current1.first).at(current1.second).pointindex[j1];
						if(!(m_grid->getPoint(pointindex3).isUnused()))
							continue;

						vect tempnorm;
						if(pointindex1 ==7 && pointindex2 ==9 && pointindex3 == 43)
							printf("this");
						if(!(point::testNormal(m_grid->pointsdatabase->points[pointindex1],m_grid->pointsdatabase->points[pointindex2],m_grid->pointsdatabase->points[pointindex3],tempnorm)))
							continue;

						if(!buildTriangle(m_grid,pointindex1,pointindex2,pointindex3,ball_center,ball_radius,tempnorm))
							continue;

						t_valid = testTriangleValidity(m_grid, neighborhood,ball_center,ball_radius);

						if(t_valid == true)
						{
							found = true;
							m_grid->currentcellindex += 1;
							break;
						}
					}
					if(t_valid == true)
					{
						break;
					}
				}
				j++;
			}
			i++;
		}
		if(found == true)
		{
			_pointindex1 = pointindex1;
			_pointindex2 = pointindex2;
			_pointindex3 = pointindex3;
		}
	}while(m_grid->currentcellindex<gridsize && !found);

	return found;
}

bool testTriangleValidity(grid *m_grid, vector<int3> &neighborhood, point3D ball_center, double ball_radius)
{
	int iupbound = neighborhood.size();
	for(int i = 0;i<iupbound;i++)
	{
		int3 current = neighborhood[i];
		int jupbound = m_grid->cells.at(current.third).at(current.first).at(current.second).pointnum;
		for(int j = 0;j<jupbound;j++)
		{
			long pointindex = m_grid->cells.at(current.third).at(current.first).at(current.second).pointindex[j];

			point3D pos = m_grid->pointsdatabase->points[pointindex].position;

			if(point3D::distance2(pos,ball_center) < ball_radius*ball_radius-0.00000001)
				return false;

			
		}
	}
		if(ball_center.x<0.6&&ball_center.x>0.4&&ball_center.y<0.6&&ball_center.y>0.4&&ball_center.z<0.6&&ball_center.z>0.4)
				int kkkkk = 0;
	return true;
}

bool buildTriangle(grid *m_grid, long &pointindex1, long &pointindex2, long &pointindex3, point3D &ballcenter, double ballradius,vect outnorm)
{
	if(pointindex1 == pointindex2 || pointindex1 == pointindex3 || pointindex2 == pointindex3)
		return false;

	point3D p1 = m_grid->getPoint3D(pointindex1);
	point3D p2 = m_grid->getPoint3D(pointindex2);
	point3D p3 = m_grid->getPoint3D(pointindex3);

	vect v12(p2.x-p1.x,p2.y-p1.y,p2.z-p1.z);
	vect v23(p3.x-p2.x,p3.y-p2.y,p3.z-p2.z);
	vect v31(p1.x-p3.x,p1.y-p3.y,p1.z-p3.z);

	double a = v23.norm();
	double b = v31.norm();
	double c = v12.norm();

	double R = a*b*c/sqrt((a+b+c)*(a+b-c)*(a+c-b)*(b+c-a));

	if(R > ballradius)
		return false;

	vect b1 = v12.normalize();
	vect b3 = outnorm.normalize();
	vect b2 = (vect::cross(b3,b1)).normalize();

	double l1 = c/2;
	double l2;
	
	if(vect::dot(v23,v31)<0)
		l2 = sqrt(abs(R*R-l1*l1));
	else
		l2 = -sqrt(abs(R*R-l1*l1));
	double l3 = sqrt(ballradius*ballradius-R*R);

	ballcenter = point3D(p1.x+b1.x*l1+b2.x*l2+b3.x*l3,p1.y+b1.y*l1+b2.y*l2+b3.y*l3,p1.z+b1.z*l1+b2.z*l2+b3.z*l3);

	return true;
}

bool buildTriangle(point3D ballcenter, double ballradius, grid *m_grid, long &pointindex1, long &pointindex2, long &pointindex3,TriangulationHandler *TH)
{
	triangle *newt = new triangle;

	newt->idx_i = pointindex1;
	newt->idx_j = pointindex2;
	newt->idx_k = pointindex3;
	newt->t_ij = NULL;
	newt->t_jk = NULL;
	newt->t_ki = NULL;

	edge *e12 = new edge(pointindex1,pointindex2,pointindex3,ballcenter);
	edge *e23 = new edge(pointindex2,pointindex3,pointindex1,ballcenter);
	edge *e31 = new edge(pointindex3,pointindex1,pointindex2,ballcenter);

	e12->sidelink = newt;
	e12->startpoint = edge::FIRSTPOINT;
	e12->next = e23;
	e12->pre = e31;

	e23->sidelink = newt;
	e23->startpoint = edge::SECONDPOINT;
	e23->next = e31;
	e23->pre = e12;

	e31->sidelink = newt;
	e31->startpoint = edge::THIRDPOINT;
	e31->next = e12;
	e31->pre = e23;

	e12->ishead = true;
	if(e12->flag != edge::ACTIVE && e12->flag != edge::BOUNDARY && e12->flag != edge::DELETED)
				int kkkkk = 0;
	TH->edfr.loopheads.push_back(e12);
	TH->edfr.loopnum += 1;
	if(TH->edfr.loopnum == 15)
				int kkkkk = 0;

	TH->frontEdgeQueue.push_back(e23);
	TH->frontEdgeQueue.push_back(e31);
	TH->frontEdgeQueue.push_back(e12);

	TH->triangleList.push_back(newt);

	point *p1 = &(m_grid->pointsdatabase->points[pointindex1]);
	p1->outedges.push_back(e12);
	p1->inedges.push_back(e31);
	p1->flag = point::ONFRONT;

	point *p2 = &(m_grid->pointsdatabase->points[pointindex2]);
	p2->outedges.push_back(e23);
	p2->inedges.push_back(e12);
	p2->flag = point::ONFRONT;

	point *p3 = &(m_grid->pointsdatabase->points[pointindex3]);
	p3->outedges.push_back(e31);
	p3->inedges.push_back(e23);
	p3->flag = point::ONFRONT;

	int3 tempindex;
	m_grid->locatePoint(pointindex1,tempindex);
	m_grid->cells.at(tempindex.third).at(tempindex.first).at(tempindex.second).activateCell();

	m_grid->locatePoint(pointindex2,tempindex);
	m_grid->cells.at(tempindex.third).at(tempindex.first).at(tempindex.second).activateCell();

	m_grid->locatePoint(pointindex3,tempindex);
	m_grid->cells.at(tempindex.third).at(tempindex.first).at(tempindex.second).activateCell();


	return true;
}


