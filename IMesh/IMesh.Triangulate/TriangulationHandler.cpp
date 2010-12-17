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

		while((currentaxis = getActiveEdge(this)) != NULL)
		{
			printf("\ngetActiveEdge()");
			long newpointindex = ballPivot(currentaxis,modelgrid,ball_radius,this);
			{
				//OnEdgeActivated(currentaxis); //: TODO: CHANGED!
				triangle* newTriangel = triangleList[triangleList.size() - 1];
				//OnTriangleCreated(newTriangel);
			}
			
			printf("\nballPivot()");
		}
   
		long seedindex1,seedindex2,seedindex3;
		point3D ball_center;
		if(findSeedTriangle(modelgrid,seedindex1,seedindex2,seedindex3,ball_center,ball_radius,this))
		{
			printf("\nfindSeedTriangle");
			buildTriangle(ball_center,ball_radius,modelgrid,seedindex1,seedindex2,seedindex3,this);
			printf("\nbuildTriangle");
		}
		else
			return;
	}
}
//void TriangulationHandler::OnEdgeActivated(edge* currentAxis)
//{
//	EdgeEventArg arg;
//	EdgeEventArg::EventType type = EdgeEventArg::Activatied;
//	arg.Initialize(type, 
//					currentAxis, &edfr, 
//					apl, &triangleList, &frontEdgeQueue);
//	void* source = currentAxis;
//	
//	// The change is originated by "source", and
//	// Influenced variables would be "arg"
//	m_edgeEvent.OnNotify(source, arg);
//}
//
//void TriangulationHandler::OnTriangleCreated(triangle* newTriangel)
//{
//
//}
