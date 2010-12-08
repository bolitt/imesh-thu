#include "StdAfx.h"
#include "Scene.h"

namespace IMesh { namespace UI { namespace Models {

Scene::Scene(void)
{
	Initialize();
}


Scene::~Scene(void)
{

}

void Scene::Initialize()
{
	m_baseLayer.m_children.push_back(&m_worldGrid);
	m_baseLayer.m_children.push_back(&m_worldAxis);
}

void Scene::OnRender()
{
	m_baseLayer.OnRender();
	m_overLayer.OnRender();
}

} } }
