#include "EdgePivot.h"

edge *getActiveEdge()
{
	edge *e = NULL;

	while(!frontEdgeQueue.empty() && e == NULL)
	{
		edge *f = frontEdgeQueue.front();

		if(f->flag != edge::ACTIVE)
		{
			frontEdgeQueue.pop_front();
			if(f->flag == edge::DELETED)
				delete f;
			continue;
		}

		e = f;
		frontEdgeQueue.pop_front();
	}

	return e;
}

long ballPivot(edge *edgeaxis, grid *m_grid, float ballradius)
{
	point3D pi = m_grid->pointsdatabase->points[edgeaxis->idx_i].position;
	point3D pj = m_grid->pointsdatabase->points[edgeaxis->idx_j].position;
	point3D pc = edgeaxis->ball_center;

	point3D m((pi.x+pj.x)*0.5,(pi.y+pj.y)*0.5,(pi.z+pj.z)*0.5);

	vect vx(pc.x-m.x,pc.y-m.y,pc.z-m.z);
	vect vz(pj.x-pi.x,pj.y-pi.y,pj.z-pi.z);
	vect vy = vect::cross(vz,vx);

	vect nx = vx.normalize();
	vect ny = vy.normalize();
	vect nz = vz.normalize();

	float rc = vect::dot(nx,vx);

	vector<long> pointcandidates;

	m_grid->findNeighborPoints(pointcandidates,ballradius,m);

	float min_angle=100.0;
	long min_index=-1;
	int ibound = pointcandidates.size();

	for(int i = 0;i<ibound;i++)
	{
		if(pointcandidates[i] == edgeaxis->idx_i || pointcandidates[i] == edgeaxis->idx_j || pointcandidates[i] == edgeaxis->idx_o)
			continue;
		point3D ps = m_grid->pointsdatabase->points[pointcandidates[i]].position;

		vect vs(ps.x-m.x,ps.y-m.y,ps.z-m.z);

		float zs = vect::dot(vs,nz);
		if(zs>ballradius)
			continue;
		float xs = vect::dot(vs,nx);
		float ys = vect::dot(vs,ny);

		float rs = sqrt(ballradius*ballradius-zs*zs);
		float ds = sqrt(xs*xs+ys*ys);
		if(rs+rc<ds || rs+ds<rc)
			continue;

		float angle = atan2(ys,xs);
		float delta_angle = acos((rc*rc+ds*ds-rs*rs)/2/ds/rc);

		float angle1 = angle-delta_angle;
		if(angle1<0)
			angle1 += 2*3.14159265;

		//float angle2 = angle+delta_angle;
		//if(angle2>2*3.14159265)
		//	angle2 -= 2*3.14159265;

		if(angle1<min_angle)
		{
			min_angle = angle1;
			min_index = pointcandidates[i];
		}
	}

	if(min_index == -1 || m_grid->pointsdatabase->points[min_index].flag == point::INNER)
	{
		edgeaxis->flag = edge::BOUNDARY;
		return -1;
	}
	vect temp;
	if(!(point::testNormal(m_grid->pointsdatabase->points[edgeaxis->idx_i],m_grid->pointsdatabase->points[min_index],m_grid->pointsdatabase->points[edgeaxis->idx_j],temp)))
	{
		edgeaxis->flag = edge::BOUNDARY;
		return -1;
	}

	float xoffset = rc*cos(min_angle);
	float yoffset = rc*sin(min_angle);

	point3D newballcenter(m.x+xoffset*nx.x+yoffset*ny.x,m.y+xoffset*nx.y+yoffset*ny.y,m.z+xoffset*nx.z+yoffset*ny.z);

	joinEdge(edgeaxis, min_index, m_grid, newballcenter);

	return min_index;
}

void joinEdge(edge *edgeaxis, long pointindex, grid *m_grid, point3D ballcenter)
{
	triangle *newt= new triangle;

	newt->idx_i = edgeaxis->idx_i;
	newt->idx_j = pointindex;
	newt->idx_k = edgeaxis->idx_j;
	newt->t_ij = NULL;
	newt->t_jk = NULL;
	newt->t_ki = edgeaxis->sidelink;

	switch(edgeaxis->startpoint)
	{
	case edge::FIRSTPOINT:
		edgeaxis->sidelink->t_ij = newt;
		break;
	case edge::SECONDPOINT:
		edgeaxis->sidelink->t_jk = newt;
		break;
	case edge::THIRDPOINT:
		edgeaxis->sidelink->t_ki = newt;
	};

	edge *ip = new edge(edgeaxis->idx_i,pointindex,edgeaxis->idx_j,ballcenter);
	edge *pj = new edge(pointindex,edgeaxis->idx_j,edgeaxis->idx_i,ballcenter);

	ip->sidelink = newt;
	ip->startpoint = edge::FIRSTPOINT;
	ip->next = pj;
	ip->pre = edgeaxis->pre;
	edgeaxis->pre->next = ip;

	pj->sidelink = newt;
	pj->startpoint = edge::SECONDPOINT;
	pj->next = edgeaxis->next;
	pj->pre = ip;
	edgeaxis->next->pre = pj;

	triangleList.push_back(newt);

	point *p1 = &(m_grid->pointsdatabase->points[edgeaxis->idx_i]);
	point *p2 = &(m_grid->pointsdatabase->points[pointindex]);
	point *p3 = &(m_grid->pointsdatabase->points[edgeaxis->idx_j]);

	edgeaxis->next = ip;
	deleteEdgefromPoint(edgeaxis,p1,true);
	deleteEdgefromPoint(edgeaxis,p3,false);
	edgeaxis->flag = edge::DELETED;
	deleteEdge(edgeaxis);
	
	bool glued1 = false;
	bool glued2 = false;

	if(p2->flag == point::ONFRONT)
	{
		
		for(int i = 0;i < p2->outedges.size();i++)
		{
			if(shouldGlue(ip,p2->outedges[i]))
			{
				//glue them!
				glueEdges(ip,p2->outedges[i],p1,p2);
				glued1 = true;
				break;
			}
		}
		for(int j = 0;j < p2->inedges.size();j++)
		{
			if(shouldGlue(pj,p2->inedges[j]))
			{
				//glue them!
				glueEdges(pj,p2->inedges[j],p2,p3);
				glued2 = true;
				break;
			}
		}
	}
	else
	{
		//cell.activate
		p2->flag = point::ONFRONT;
		int3 tempindex;
		m_grid->locatePoint(p2->position,tempindex);
		m_grid->cells.at(tempindex.third).at(tempindex.first).at(tempindex.second).activateCell();

	}

	if(glued1 == false)
	{
		//add edge1 
		p1->outedges.push_back(ip);
		p2->inedges.push_back(ip);
		frontEdgeQueue.push_back(ip);
	}
	if(glued2 == false)
	{
		//add edge2
		p2->outedges.push_back(pj);
		p3->inedges.push_back(pj);
		frontEdgeQueue.push_back(pj);
	}

}

bool shouldGlue(edge *newedge, edge *originedge)
{
	if(newedge->idx_i == originedge->idx_j && newedge->idx_j == originedge->idx_i)
		return true;
	return false;
}
bool edgeEqual(edge *e1, edge *e2)
{
	if(e1->idx_i == e2->idx_i && e1->idx_j == e2->idx_j)
		return true;
	return false;
}


void deleteEdge(edge *e)
{
	//e->next->pre = e->pre;
	//e->pre->next = e->next;
	if(e->ishead)
	{
		int i;
		for(i = 0;i<edfr.loopheads.size();i++)
			if(edgeEqual(edfr.loopheads[i],e))
				break;

		e->ishead = false;
		edfr.loopheads[i] = e->next;
		e->next->ishead = true;
		if(e->ishead)
		{
			edfr.loopheads.erase(edfr.loopheads.begin()+i);
			edfr.loopnum -= 1;
		}
	}
		
	if(e->flag == edge::ACTIVE)
		e->flag = edge::DELETED;
	else
		delete e;
	//
}

void deleteEdgefromPoint(edge *e, point *p, bool oi)
{
	int i;
	if(oi == true)//o
	{
		for(i = 0;i<p->outedges.size();i++)
			if(edgeEqual(p->outedges[i],e))
				break;
		p->outedges.erase(p->outedges.begin()+i);
	}
	else//i
	{
		for(i = 0;i<p->inedges.size();i++)
			if(edgeEqual(p->inedges[i],e))
				break;
		p->inedges.erase(p->inedges.begin()+i);
	}
}

void glueEdges(edge *newedge, edge *originedge, point *newedgei, point *newedgej)
{
	triangle *tn = newedge->sidelink;
	triangle *to = originedge->sidelink;

	switch(newedge->startpoint)
	{
	case edge::FIRSTPOINT:
		tn->t_ij = to;
		break;
	case edge::SECONDPOINT:
		tn->t_jk = to;
		break;
	case edge::THIRDPOINT:
		tn->t_ki = to;
	};
	switch(originedge->startpoint)
	{
	case edge::FIRSTPOINT:
		to->t_ij = tn;
		break;
	case edge::SECONDPOINT:
		to->t_jk = tn;
		break;
	case edge::THIRDPOINT:
		to->t_ki = tn;
	};

	bool cont = false;
	if(edgeEqual(newedge->next,originedge))
	{
		if(edgeEqual(originedge->next ,newedge))
			cont = true;

		newedge->pre->next = originedge;
		originedge->pre = newedge->pre;
		
		newedge->flag = edge::DELETED;
		deleteEdge(newedge);

		originedge->pre->next = originedge->next;
		originedge->next->pre = originedge->pre;

		deleteEdgefromPoint(originedge,newedgej,true);
		deleteEdgefromPoint(originedge,newedgei,false);

		deleteEdge(originedge);

		if(newedgej->outedges.size() == 0 && newedgej->inedges.size() == 0)
			newedgej->flag = point::INNER;
		if(cont == true && newedgei->outedges.size() == 0 && newedgei->inedges.size() == 0)
			newedgei->flag = point::INNER;

		return;
	}

	if(edgeEqual(originedge->next ,newedge))
	{
		newedge->next->pre = originedge;
		originedge->next = newedge->next;

		newedge->flag = edge::DELETED;
		deleteEdge(newedge);

		originedge->pre->next = originedge->next;
		originedge->next->pre = originedge->pre;

		deleteEdgefromPoint(originedge,newedgei,false);
		deleteEdgefromPoint(originedge,newedgej,true);

		deleteEdge(originedge);
		if(newedgei->outedges.size() == 0 && newedgei->inedges.size() == 0)
			newedgei->flag = point::INNER;

		return;
	}

	int control = 0;
	bool found = false;
	for(edge *current = newedge->next; !edgeEqual(current,newedge); current = current->next)
	{
		if(newedge->ishead)
			control = -1;
		if(current->ishead)
		{
			if(edgeEqual(current,originedge))
			{
				control = -2;
				found = true;
				break;
			}
			else
			{
				control = 1;
			}
		}
		
		if(edgeEqual(current, originedge))
		{
			found = true;
			break;
		}
	}

	if(found == true)
	{
		switch(control)
		{
		case -1: 
		case 1:
			newedge->next->pre = originedge->pre;
			newedge->pre->next = originedge->next;
			originedge->next->pre = newedge->pre;
			originedge->pre->next = newedge->next;

			newedge->flag = edge::DELETED;
			deleteEdge(newedge);

			deleteEdgefromPoint(originedge,newedgej,true);
			deleteEdgefromPoint(originedge,newedgei,false);

			originedge->next->ishead = true;
			edfr.loopheads.push_back(originedge->next);
			edfr.loopnum += 1;

			deleteEdge(originedge);

			return;
		case -2:
		case 0:
			newedge->next->pre = originedge->pre;
			newedge->pre->next = originedge->next;
			originedge->next->pre = newedge->pre;
			originedge->pre->next = newedge->next;

			deleteEdgefromPoint(originedge,newedgej,true);
			deleteEdgefromPoint(originedge,newedgei,false);

			newedge->next->ishead = true;
			edfr.loopheads.push_back(newedge->next);
			edfr.loopnum += 1;

			newedge->flag = edge::DELETED;
			deleteEdge(newedge);
			deleteEdge(originedge);

			return;
		}
	}

	edge *start = newedge->next;
	edge *temp = start;

	newedge->next->pre = originedge->pre;
	newedge->pre->next = originedge->next;
	originedge->next->pre = newedge->pre;
	originedge->pre->next = newedge->next;

	deleteEdgefromPoint(originedge,newedgej,true);
	deleteEdgefromPoint(originedge,newedgei,false);

	newedge->flag = edge::DELETED;
	deleteEdge(newedge);
	deleteEdge(originedge);


	do
	{
		if(temp->ishead)
		{
			int i;
			for(i = 0;i<edfr.loopheads.size();i++)
				if(edgeEqual(edfr.loopheads[i],temp))
					break;

			temp->ishead = false;
			edfr.loopheads.erase(edfr.loopheads.begin()+i);
			edfr.loopnum -= 1;
			break;
		}
		temp = temp->next;
	}while(!edgeEqual(temp,start));

	return;
}




			


				
