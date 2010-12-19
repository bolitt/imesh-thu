#pragma once
#include "predefs.h"
#include "TriangulationHandler.h"

extern edge *getActiveEdge(TriangulationHandler *TH);
extern long ballPivot(edge *edgeaxis,grid *m_grid, double ballradius, point3D& outBallCenter, TriangulationHandler *TH);

extern void joinEdge(edge *edgeaxis, long pointindex, grid *m_grid, point3D ballcenter, TriangulationHandler *TH);
extern void glueEdges(edge *newedge, edge *originedge, point *newedgei, point *newedgej, TriangulationHandler *TH);
extern bool shouldGlue(edge *newedge, edge *originedge);
extern void deleteEdge(edge *e, TriangulationHandler *TH);
extern bool edgeEqual(edge *e1,edge *e2);
extern void deleteEdgefromPoint(edge *e, point *p, bool oi);//o:true,i:false