#pragma once
#include "predefs.h"
#include "SeedSelection.h"
#include "EdgePivot.h"

//: TODO: CHANGED!
#include "EventCommon.h"

class TriangulationHandler{
	grid *modelgrid;
	all_point_list *apl;
	double ball_radius;

public:
	TriangulationHandler(){};
	void Initialize(vector<norm_point> &nps, int isize, int jsize, int ksize, double gridwidth,double ballradius);
	void triangulateModel();


public:

	EdgeEvent m_edgeEvent; //: TODO: CHANGED!
	void OnEdgeActivated(edge* currentAxis); //: TODO: CHANGED!
	void OnTriangleCreated(triangle* newTriangel);

};