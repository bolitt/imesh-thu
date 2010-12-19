#include "StdAfx.h"
#include "MeshHelper.h"

namespace IMesh { namespace UI {

	Vertex* MeshHelper::CreateVertexFromPoint( point& p )
	{
		point3D pos = p.position;
		Vertex* v0 = new Vertex();
		v0->m_pos._x = (float)pos.x;
		v0->m_pos._y = (float)pos.y;
		v0->m_pos._z = (float)pos.z;
		if (m_pAdjuster!= NULL) v0->m_pos = m_pAdjuster->Adjust(v0->m_pos);

		return v0;
	}

	Triangle* MeshHelper::CreateTriangleFromVertex( Vertex* pV0, Vertex* pV1, Vertex* pV2 )
	{
		Triangle* tri = new Triangle();
		tri->_pV0 = pV0;
		tri->_pV1 = pV1;
		tri->_pV2 = pV2;
		return tri;
	}

	Edge* MeshHelper::CreateEdgeFromVertex( Vertex* pV0, Vertex* pV1 )
	{
		Edge* e = new Edge();
		e->_pV0 = pV0;
		e->_pV1 = pV1;
		//e->m_color = Edge::color_type(0.5f, 0.3f, 0.7f);
		return e;
	}

} }
