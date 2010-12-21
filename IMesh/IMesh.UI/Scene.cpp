#include "StdAfx.h"
#include "Scene.h"


namespace IMesh { namespace UI { namespace Models {

Scene::Scene(void)
{
	// For Model:
}


Scene::~Scene(void)
{
}

void Scene::OnSetup()
{
	/*glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);*/

	// m_baselayer
	m_worldGrid.OnSetup();
	m_worldAxis.OnSetup();
	m_baseLayer.OnSetup();
	m_baseLayer.m_children.push_back(&m_worldGrid);
	m_baseLayer.m_children.push_back(&m_worldAxis);
	
	m_cloudLayer.OnSetup();
	m_cloudLayer.m_pAdjuster = &m_adjuster;
	
	m_meshLayer.OnSetup();
	m_meshLayer.m_pAdjuster = &m_adjuster;
	
	// m_overlayer
	//m_overLayer.m_children.push_back(&m_sphere);
	//m_overLayer.m_children.push_back(&m_triangle);
}


void Scene::OnRender()
{
	if (!m_IsVisible) return;

	parent_type::OnRender();
	_DEBUG_ONRENDER_CHECK_ERROR_();

	m_baseLayer.OnRender();
	_DEBUG_ONRENDER_CHECK_ERROR_();

	m_cloudLayer.OnRender();
	_DEBUG_ONRENDER_CHECK_ERROR_();

	/*glPushMatrix();
	{
		glDepthFunc(GL_LESS);
		GLboolean bGL_DEPTH_TEST = glIsEnabled(GL_DEPTH_TEST); glEnable(GL_DEPTH_TEST);
		GLboolean bGL_LIGHTING = glIsEnabled(GL_LIGHTING); glEnable(GL_LIGHTING);

		InitializeLighting();

		m_meshLayer.OnRender();
		_DEBUG_ONRENDER_CHECK_ERROR_();

		if (!bGL_DEPTH_TEST) glDisable(GL_DEPTH_TEST);
		if (!bGL_LIGHTING) glDisable(GL_LIGHTING);
	}
	glPopMatrix();*/

	m_meshLayer.OnRender();
	_DEBUG_ONRENDER_CHECK_ERROR_();
}

void Scene::InitializeLighting()
{
	{
		glEnable(GL_LIGHT0); glEnable(GL_LIGHT1); glEnable(GL_LIGHT2);

		GLfloat light_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };

		GLfloat light0_diffuse[] = { 0.6f, 0.0f, 0.0f, 1.0f };
		GLfloat light1_diffuse[] = { 0.0f, 0.6f, 0.0f, 1.0f };
		GLfloat light2_diffuse[] = { 0.0f, 0.0f, 0.6f, 1.0f };

		GLfloat light0_specular[] = { 0.6f, 0.0f, 0.0f, 1.0f };
		GLfloat light1_specular[] = { 0.0f, 0.6f, 0.0f, 1.0f };
		GLfloat light2_specular[] = { 0.0f, 0.0f, 0.6f, 1.0f };

		float inf = (float)Config::Navigation::DEFAULT_FAR; 

		GLfloat light0_position[] = { inf, 0.0f, 0.0f, 1.0f };
		GLfloat light1_position[] = { 0.0f, inf, 0.0f, 1.0f };
		GLfloat light2_position[] = { 0.0f, 0.0f, inf, 1.0f };

		GLfloat light0_spot_direction[] = { -1.0f, 0.0f, 0.0f };
		GLfloat light1_spot_direction[] = { 0.0f, -1.0f, 0.0f };
		GLfloat light2_spot_direction[] = { 0.0f, 0.0f, -1.0f };

		glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
		glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
		glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
		glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light0_spot_direction);

		glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
		glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
		glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
		glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light1_spot_direction);

		glLightfv(GL_LIGHT2, GL_AMBIENT, light_ambient);
		glLightfv(GL_LIGHT2, GL_DIFFUSE, light2_diffuse);
		glLightfv(GL_LIGHT2, GL_SPECULAR, light2_specular);
		glLightfv(GL_LIGHT2, GL_POSITION, light2_position);
		glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, light2_spot_direction);
	}

	{
		GLfloat mat_ambient[]= { 0.2f, 0.2f, 0.2f, 1.0f };  
		GLfloat mat_diffuse[]= { 0.8f, 0.8f, 0.8f, 1.0f }; 
		GLfloat mat_specular[] = {1.0f, 1.0f, 1.0f, 1.0f };
		GLfloat mat_shininess[] = { 50.0f };
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);  
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse); 
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	}

	{
		GLfloat light_model_ambient[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_model_ambient);

		glShadeModel(GL_SMOOTH);
	}
}


} } }
