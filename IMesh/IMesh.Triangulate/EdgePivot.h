#pragma once
#include "predefs.h"

edge *getActiveEdge();
long ballPivot(edge *edgeaxis,grid *m_grid, float ballradius);


void joinEdge(edge *edgeaxis, long pointindex, grid *m_grid, point3D ballcenter);
void glueEdges(edge *newedge, edge *originedge, point *newedgei, point *newedgej);
bool shouldGlue(edge *newedge, edge *originedge);
void deleteEdge(edge *e);
bool edgeEqual(edge *e1,edge *e2);
void deleteEdgefromPoint(edge *e, point *p, bool oi);//o:true,i:false