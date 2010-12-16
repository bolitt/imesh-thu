#include "StdAfx.h"
#include "Scene.h"


namespace IMesh { namespace UI { namespace Models {

Scene::Scene(void)
{
}


Scene::~Scene(void)
{
	for (size_t i = 0; i < m_edges.size(); ++i)
	{
		Edge* e = m_edges[i];
		Vertex* p0 = e->_pV0;
		Vertex* p1 = e->_pV1;
		delete p0;
		delete p1;
		delete e;
	}
}

void Scene::OnSetup()
{
	m_worldGrid.OnSetup();
	m_worldAxis.OnSetup();
	m_sphere.OnSetup();
	m_triangle.OnSetup();

	// m_baselayer
	m_baseLayer.m_children.push_back(&m_worldGrid);
	m_baseLayer.m_children.push_back(&m_worldAxis);
	
	// m_overlayer
	//m_overLayer.m_children.push_back(&m_sphere);
	//m_overLayer.m_children.push_back(&m_triangle); 

	{
		using namespace IMesh::UI;
		using namespace IMesh::Norm;
		CloudLoader loader;
		loader.Initialize();
		std::vector<Num::Vec3f>& points = loader.GetPoints();
		std::vector<Num::Vec3f>& norms = loader.GetNorms();
		ASSERT(points.size() == norms.size());

		float ratio = 30;
		for (size_t i = 0; i < points.size(); i++) {
			Num::Vec3f& point = points[i];
			point.Mul(ratio);
			Num::Vec3f& norm = norms[i];

			Vertex* v0 = new Vertex();
			v0->m_id = i;
			v0->m_pos = point;
			m_verties.push_back(v0);

			Vertex* v1 = new Vertex();
			v1->m_id = i;
			v1->m_pos = point + norm;

			Edge* e = new Edge();
			e->m_id = i;
			e->_pV0 = v0;
			e->_pV1 = v1;
			m_edges.push_back(e);
			
			m_overLayer.m_children.push_back(v0);
			m_overLayer.m_children.push_back(e);
		}

	}
}

void Scene::OnRender()
{
	parent_type::OnRender();
	_DEBUG_ONRENDER_CHECK_ERROR_();

	m_baseLayer.OnRender();
	_DEBUG_ONRENDER_CHECK_ERROR_();

	m_overLayer.OnRender();
	_DEBUG_ONRENDER_CHECK_ERROR_();

	m_demoLayer.OnRender();
	_DEBUG_ONRENDER_CHECK_ERROR_();
}

void Scene::OnDemoLayerUpdated()
{
	OnRender();
}

} } }
