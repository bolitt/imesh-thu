#include "StdAfx.h"
#include "EdgeEventHandler.h"
#include "Visualizer.h"

namespace IMesh { namespace UI {

using namespace IMesh::UI::Models;

EdgeEventListener::EdgeEventListener(void)
{
}


EdgeEventListener::~EdgeEventListener(void)
{
}

void EdgeEventListener::Initialize( IMesh::UI::CVisualizer* pVisualizer, layer_type* pDemoLayer )
{
	m_pVisualizer = pVisualizer;
	m_pDemoLayer = pDemoLayer;
}

void EdgeEventListener::OnHandle( void* source, const IMesh::Interface::EventArg& arg )
{
	edge& newEdge = *((edge*) source);
	EdgeEventArg& edgeEventArg = (EdgeEventArg&) arg;

	switch(edgeEventArg.m_eventType)
	{
		case EdgeEventArg::Activatied: 
		{
			UpdateLayer(newEdge, edgeEventArg);
			break;
		}
			
		default:
		{
			new std::exception("Not Support Exception.");
		}
	}
	/*DWORD millonSecond = 100;
	
	while(true) 
	{
		Sleep(millonSecond);
	} */
}

static Vertex* CreateVertexFromPoint(point& p)
{
	point3D pos = p.position;
	Vertex* v0 = new Vertex();
	float ratio = 30.0f;
	v0->m_pos._x = (float)pos.x * ratio;
	v0->m_pos._y = (float)pos.y * ratio;
	v0->m_pos._z = (float)pos.z * ratio;
	return v0;
}

static Triangle* CreateTriangleFromVertex(Vertex* pV0, Vertex* pV1, Vertex* pV2)
{
	Triangle* tri = new Triangle();
	tri->_pV0 = pV0;
	tri->_pV1 = pV1;
	tri->_pV2 = pV2;
	return tri;
}

static Edge* CreateEdgeFromVertex(Vertex* pV0, Vertex* pV1)
{
	Edge* e = new Edge();
	e->_pV0 = pV0;
	e->_pV1 = pV1;
	//e->m_color = Edge::color_type(0.5f, 0.3f, 0.7f);
	return e;
}


void EdgeEventListener::UpdateLayer( edge& newEdge, EdgeEventArg& edgeEventArg )
{
	typedef vector<triangle* > triangle_list_type;
	typedef vector<point> points_type;
	if (m_pDemoLayer != NULL) 
	{
		Clear();

		triangle_list_type& triangles = *(edgeEventArg.m_pTriangleList);
		points_type& points = edgeEventArg.m_pAllPointList->points;

		for (size_t i = 0; i < triangles.size(); ++i) 
		{
			triangle& t = *(triangles[i]);
			point& p0 = points[t.idx_i];
			point& p1 = points[t.idx_j];
			point& p2 = points[t.idx_k];
			
			Vertex* pV0 = CreateVertexFromPoint(p0);
			Vertex* pV1 = CreateVertexFromPoint(p1);
			Vertex* pV2 = CreateVertexFromPoint(p2);

			m_verticesHolder.push_back(pV0);
			m_verticesHolder.push_back(pV1);
			m_verticesHolder.push_back(pV2);
			
			Triangle* pT = CreateTriangleFromVertex(pV0, pV1, pV2);
			m_trianglesHolder.push_back(pT);

			Edge* e0 = CreateEdgeFromVertex(pV0, pV1);
			Edge* e1 = CreateEdgeFromVertex(pV1, pV2);
			Edge* e2 = CreateEdgeFromVertex(pV2, pV0);
			m_edgesHolder.push_back(e0);
			m_edgesHolder.push_back(e1);
			m_edgesHolder.push_back(e2);
		}

		for (size_t i = 0; i < m_trianglesHolder.size(); ++i)
		{
			Triangle& refTri = * m_trianglesHolder[i];
			//m_pDemoLayer->m_children.push_back(&refTri);
		}
		for (size_t i = 0; i < m_edgesHolder.size(); ++i)
		{
			Edge& refEdge = * m_edgesHolder[i];
			m_pDemoLayer->m_children.push_back(&refEdge);
		}
	}

	m_pVisualizer->OnRender();
}

void EdgeEventListener::Clear()
{
	m_pDemoLayer->m_children.clear();
	
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



} }
