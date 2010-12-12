#pragma once
#include "predefs.h"


bool findSeedTriangle(grid *m_grid, long &_pointindex1, long &_pointindex2, long &_pointindex3, point3D &ball_center, float ball_radius);

//long pickPoint(all_point_list *apl);

//bool buildTriangle(edge *c_edge, point *newp, grid *m_grid);
bool buildTriangle(grid *m_grid, long &pointindex1, long &pointindex2, long &pointindex3, point3D &ballcenter, float ballradius,vect outnorm);
bool buildTriangle(point3D ballcenter, float ballradius, grid *m_grid, long &pointindex1, long &pointindex2, long &pointindex3);

bool testTriangleValidity(grid *m_grid, vector<int3> &neighborhood, point3D ball_center, float ball_radius);
