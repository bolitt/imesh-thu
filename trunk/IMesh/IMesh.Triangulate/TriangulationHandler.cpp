#include "TriangulationHandler.h"

void TriangulationHandler::Initialize(vector<norm_point> &nps, int isize, int jsize, int ksize, double gridwidth, double ballradius)
{
	apl = new all_point_list(nps);
	modelgrid = new grid(isize,jsize,ksize,apl,gridwidth);
	ballRadius = ballradius;

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
			edge currentEdge = *currentaxis;
			point3D ball_center;
			long newpointindex = ballPivot(currentaxis, modelgrid, ballRadius, ball_center, this);
			printf("\nballPivot()");

			// Events:
			{
				this->ballCenter = ball_center;
				OnEdgeActivated(&currentEdge);
				triangle* newTriangel = triangleList[triangleList.size() - 1];
				OnTriangleCreated(newTriangel);
			}
		}
   
		long seedindex1,seedindex2,seedindex3;
		point3D ball_center;
		if(findSeedTriangle(modelgrid, seedindex1, seedindex2, seedindex3, ball_center, ballRadius, this))
		{
			printf("\nfindSeedTriangle");
			buildTriangle(ball_center,ballRadius,modelgrid,seedindex1,seedindex2,seedindex3,this);
			printf("\nbuildTriangle");
			
			// Events:
			{
				this->ballCenter = ball_center;
				triangle* newTriangel = triangleList[triangleList.size() - 1];
				OnSeedTriangleFound(newTriangel);
				OnTriangleCreated(newTriangel);
			}
		}
		else 
		{
			break;
		}
	}
	OnCompleted();
}
void TriangulationHandler::OnEdgeActivated(edge* currentAxis)
{
	TriangulateEventArg arg;
	TriangulateEventArg::EventType type = TriangulateEventArg::EdgeActivatied;
	arg.Initialize(type, currentAxis, this);
	void* source = currentAxis;
	
	// The change is originated by "source", and
	// Influenced variables would be "arg"
	m_event.OnNotify(source, arg);
}

void TriangulationHandler::OnTriangleCreated(triangle* newTriangle)
{
	TriangulateEventArg arg;
	TriangulateEventArg::EventType type = TriangulateEventArg::TriangleCreated;
	arg.Initialize(type, newTriangle, this);
	void* source = newTriangle;

	m_event.OnNotify(source, arg);
}


void TriangulationHandler::OnSeedTriangleFound( triangle* seedTriangle )
{
	TriangulateEventArg arg;
	TriangulateEventArg::EventType type = TriangulateEventArg::SeedTriangleFound;
	arg.Initialize(type, seedTriangle, this);
	void* source = seedTriangle;

	m_event.OnNotify(source, arg);
}

void TriangulationHandler::OnCompleted()
{
	TriangulateEventArg arg;
	TriangulateEventArg::EventType type = TriangulateEventArg::Completed;
	arg.Initialize(type, this);
	void* source = NULL;

	m_event.OnNotify(source, arg);
}
