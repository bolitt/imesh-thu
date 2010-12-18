#include "StdAfx.h"
#include "TriangulateHelper.h"

namespace IMesh { namespace UI {

	Vertex* TriangularHelper::CreateVertexFromPoint( point& p )
	{
		point3D pos = p.position;
		Vertex* v0 = new Vertex();
		float ratio = 30.0f;
		v0->m_pos._x = (float)pos.x * ratio;
		v0->m_pos._y = (float)pos.y * ratio;
		v0->m_pos._z = (float)pos.z * ratio;
		return v0;
	}

	Triangle* TriangularHelper::CreateTriangleFromVertex( Vertex* pV0, Vertex* pV1, Vertex* pV2 )
	{
		Triangle* tri = new Triangle();
		tri->_pV0 = pV0;
		tri->_pV1 = pV1;
		tri->_pV2 = pV2;
		return tri;
	}

	Edge* TriangularHelper::CreateEdgeFromVertex( Vertex* pV0, Vertex* pV1 )
	{
		Edge* e = new Edge();
		e->_pV0 = pV0;
		e->_pV1 = pV1;
		//e->m_color = Edge::color_type(0.5f, 0.3f, 0.7f);
		return e;
	}

} }
