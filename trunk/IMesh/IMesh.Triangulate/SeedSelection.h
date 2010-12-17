#pragma once
#include "predefs.h"
#include "TriangulationHandler.h"


extern bool findSeedTriangle(grid *m_grid, long &_pointindex1, long &_pointindex2, long &_pointindex3, point3D &ball_center, double ball_radius, TriangulationHandler *TH);

//long pickPoint(all_point_list *apl);

//bool buildTriangle(edge *c_edge, point *newp, grid *m_grid);
extern bool buildTriangle(grid *m_grid, long &pointindex1, long &pointindex2, long &pointindex3, point3D &ballcenter, double ballradius,vect outnorm);
extern bool buildTriangle(point3D ballcenter, double ballradius, grid *m_grid, long &pointindex1, long &pointindex2, long &pointindex3, TriangulationHandler *TH);

extern bool testTriangleValidity(grid *m_grid, vector<int3> &neighborhood, point3D ball_center, double ball_radius);
