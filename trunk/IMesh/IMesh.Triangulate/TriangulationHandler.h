#pragma once
#include "predefs.h"
#include "SeedSelection.h"
#include "EdgePivot.h"

class TriangulationHandler{
	grid *modelgrid;
	all_point_list *apl;
	float ball_radius;

public:
	TriangulationHandler(){};
	void Initialize(vector<norm_point> &nps, int isize, int jsize, int ksize, float gridwidth,float ballradius);
	void triangulateModel();
};