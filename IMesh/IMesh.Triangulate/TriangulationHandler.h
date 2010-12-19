#pragma once
#include "predefs.h"
#include "SeedSelection.h"
#include "EdgePivot.h"

//: TODO: CHANGED!
#include "EventCommon.h"


class TriangulationHandler
{
	grid *modelgrid;

public:
	all_point_list *apl;
	double ballRadius;
	point3D ballCenter;

public:
	vector<triangle *> triangleList;
	edgefront edfr;
	deque<edge *> frontEdgeQueue;
	

	TriangulationHandler(){};
	void Initialize(vector<norm_point> &nps, int isize, int jsize, int ksize, double gridwidth,double ballradius);
	void triangulateModel();
	

public:
	TriangulateEvent m_event; //: TODO: CHANGED!
	void OnEdgeActivated(edge* currentAxis); //: TODO: CHANGED!
	void OnTriangleCreated(triangle* newTriangle);
	void OnSeedTriangleFound(triangle* seedTriangle);
	void OnCompleted();
};