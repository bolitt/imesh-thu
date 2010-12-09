#include "StdAfx.h"
#include "Scene.h"

namespace IMesh { namespace UI { namespace Models {

Scene::Scene(void)
{
}


Scene::~Scene(void)
{
}

void Scene::OnSetup()
{
	m_worldGrid.OnSetup();
	m_worldAxis.OnSetup();
	m_sphere.OnSetup();
	m_triangle.OnSetup();

	m_baseLayer.m_children.push_back(&m_worldGrid);
	m_baseLayer.m_children.push_back(&m_worldAxis);
	
	m_overLayer.m_children.push_back(&m_sphere);
	m_overLayer.m_children.push_back(&m_triangle);
}

void Scene::OnRender()
{
	parent_type::OnRender();
	_DEBUG_ONRENDER_CHECK_ERROR_();

	m_baseLayer.OnRender();
	_DEBUG_ONRENDER_CHECK_ERROR_();

	m_overLayer.OnRender();
	_DEBUG_ONRENDER_CHECK_ERROR_();
}

} } }
