#include "TriangulationHandler.h"

void TriangulationHandler::Initialize(vector<norm_point> &nps, int isize, int jsize, int ksize, double gridwidth, double ballradius)
{
	apl = new all_point_list(nps);
	modelgrid = new grid(isize,jsize,ksize,apl,gridwidth);
	ball_radius = ballradius;

	modelgrid->initialize();

}

void TriangulationHandler::triangulateModel()
{
	while(true)
	{
		edge *currentaxis;

		while((currentaxis = getActiveEdge()) != NULL)
		{
			printf("\ngetActiveEdge()");
			long newpointindex = ballPivot(currentaxis,modelgrid,ball_radius);
			printf("\nballPivot()");
		}
		

		long seedindex1,seedindex2,seedindex3;
		point3D ball_center;
		if(findSeedTriangle(modelgrid,seedindex1,seedindex2,seedindex3,ball_center,ball_radius))
		{
			printf("\nfindSeedTriangle");
			buildTriangle(ball_center,ball_radius,modelgrid,seedindex1,seedindex2,seedindex3);
			printf("\buildTriangle");
		}
		else
			return;
	}
}
