#include "Vec.h"


namespace IMesh { //: namespace IMesh
namespace Norm { //: namespace IMesh::Norm

	
		double SquareOfDistance( Vector3 &u, Vector3 &v)
		{
			return (u.x-v.x)*(u.x-v.x)+(u.y-v.y)*(u.y-v.y)+(u.z-v.z)*(u.z-v.z);
		}

		bool cmplength(Edge e, Edge f)
		{
			if ( e.weight == f.weight )
				if( e.u == f.u )
					return e.v < f.v;
				else
					return e.u < f.u;
			else
				return e.weight < f.weight;
		}


		Edge::Edge(int i, int j, double w){
				u=i,v=j;
				weight = w;
		}


} ///:~ namespace IMesh::Norm
} ///:~ namespace IMesh