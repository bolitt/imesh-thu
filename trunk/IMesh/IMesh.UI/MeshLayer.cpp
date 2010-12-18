#include "StdAfx.h"
#include "MeshLayer.h"
#include "TriangulateHelper.h"

namespace IMesh { namespace UI { namespace Models {


MeshLayer::MeshLayer(void)
{
}


MeshLayer::~MeshLayer(void)
{
	ClearLayer();
}



void MeshLayer::ClearLayer()
{	
	this->m_children.clear();

	for (size_t i = 0; i < m_verticesHolder.size(); ++i)
	{
		delete m_verticesHolder[i];
	}
	m_verticesHolder.clear();

	for (size_t i = 0; i < m_trianglesHolder.size(); ++i)
	{
		delete m_trianglesHolder[i];
	}
	m_trianglesHolder.clear();

	for (size_t i = 0; i < m_edgesHolder.size(); ++i)
	{
		delete m_edgesHolder[i];
	}
	m_edgesHolder.clear();

}

void MeshLayer::UpdateLayer( triangle_list_type &triangles, points_type& points ) 
{
	ClearLayer();
	
	IMesh::UI::TriangularHelper helper;

	for (size_t i = 0; i < triangles.size(); ++i) 
	{
		triangle& t = *(triangles[i]);
		point& p0 = points[t.idx_i];
		point& p1 = points[t.idx_j];
		point& p2 = points[t.idx_k];

		Vertex* pV0 = helper.CreateVertexFromPoint(p0);
		pV0->m_id = t.idx_i;
		Vertex* pV1 = helper.CreateVertexFromPoint(p1);
		pV1->m_id = t.idx_j;
		Vertex* pV2 = helper.CreateVertexFromPoint(p2);
		pV2->m_id = t.idx_k;

		m_verticesHolder.push_back(pV0);
		m_verticesHolder.push_back(pV1);
		m_verticesHolder.push_back(pV2);

		Triangle* pT = helper.CreateTriangleFromVertex(pV0, pV1, pV2);
		pT->m_id = i;
		m_trianglesHolder.push_back(pT);

		Edge* e0 = helper.CreateEdgeFromVertex(pV0, pV1);
		e0->m_id = 3 * i;
		Edge* e1 = helper.CreateEdgeFromVertex(pV1, pV2);
		e1->m_id = 3 * i + 1;
		Edge* e2 = helper.CreateEdgeFromVertex(pV2, pV0);
		e2->m_id = 3 * i + 2;
		m_edgesHolder.push_back(e0);
		m_edgesHolder.push_back(e1);
		m_edgesHolder.push_back(e2);
	}

	for (size_t i = 0; i < m_trianglesHolder.size(); ++i)
	{
		Triangle& refTri = * m_trianglesHolder[i];
		this->m_children.push_back(&refTri);
	}
	for (size_t i = 0; i < m_edgesHolder.size(); ++i)
	{
		Edge& refEdge = * m_edgesHolder[i];
		this->m_children.push_back(&refEdge);
	}

}


void MeshLayer::OnSetup()
{
	m_sphere.OnSetup();
	m_sphere.m_pos = Num::Vec3f(-20, -20, -20);

	m_triangle.OnSetup();
	m_triangle._pV0 = new Vertex();
	m_triangle._pV1 = new Vertex();
	m_triangle._pV2 = new Vertex();
	m_triangle._pV0->m_pos = Num::Vec3f(-10.0f, -10.0f, -1.0f);
	m_triangle._pV1->m_pos = Num::Vec3f(0.0f, 0.0f, -1.0f);
	m_triangle._pV2->m_pos = Num::Vec3f(-10.0f, 0.0f, -1.0f);
	m_triangle.m_fill = Triangle::color_type(1.0f, 1.0f, 0.0f);
}

void MeshLayer::OnRender()
{
	if (!m_IsVisible) return;
	
	m_sphere.OnRender();
	_DEBUG_ONRENDER_CHECK_ERROR_();

	m_triangle.OnRender();
	_DEBUG_ONRENDER_CHECK_ERROR_();

	parent_type::OnRender();
	_DEBUG_ONRENDER_CHECK_ERROR_();
}

} } }
