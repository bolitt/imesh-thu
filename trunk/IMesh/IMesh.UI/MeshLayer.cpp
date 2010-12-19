#include "StdAfx.h"
#include "MeshLayer.h"
#include "MeshHelper.h"

namespace IMesh { namespace UI { namespace Models {

using namespace IMesh::UI::Config;

MeshLayer::MeshLayer(void)
{
	m_pAdjuster = NULL;

	m_pCurrentEdge = NULL;
	m_pCurrentTriangle = NULL;
}


MeshLayer::~MeshLayer(void)
{
	ClearLayer();
	ClearCurrentEdge();
	ClearCurrentTriangle();
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
	
	IMesh::UI::MeshHelper helper(m_pAdjuster);

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
	m_sphere.m_radius = 0.05f;
	m_sphere.m_pos = Num::Vec3f(0, 0, 0);

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
	
	glPushMatrix();
	{
		glDepthFunc(GL_LESS);
		GLboolean bGL_DEPTH_TEST = glIsEnabled(GL_DEPTH_TEST); glEnable(GL_DEPTH_TEST);
		GLboolean bGL_LIGHTING = glIsEnabled(GL_LIGHTING); glEnable(GL_LIGHTING);
		InitializeLighting();

		//m_triangle.OnRender();
		//_DEBUG_ONRENDER_CHECK_ERROR_();

		m_sphere.OnRender();
		_DEBUG_ONRENDER_CHECK_ERROR_();

		parent_type::OnRender();
		_DEBUG_ONRENDER_CHECK_ERROR_();

		if (!bGL_DEPTH_TEST) glDisable(GL_DEPTH_TEST);
		if (!bGL_LIGHTING) glDisable(GL_LIGHTING);
	}
	glPopMatrix();

	if (m_pCurrentEdge != NULL) m_pCurrentEdge->OnRender();
	if (m_pCurrentTriangle != NULL) m_pCurrentTriangle->OnRender();
	_DEBUG_ONRENDER_CHECK_ERROR_();

}

void MeshLayer::InitializeLightEnum(GLenum lightEnum, 
						GLfloat* ambient, GLfloat* diffuse, GLfloat* specular, 
						GLfloat* position, GLfloat* spotDirection )
{
	glLightfv(lightEnum, GL_AMBIENT, ambient);
	glLightfv(lightEnum, GL_DIFFUSE, diffuse);
	glLightfv(lightEnum, GL_SPECULAR, specular);
	glLightfv(lightEnum, GL_POSITION, position);
	glLightfv(lightEnum, GL_SPOT_DIRECTION, spotDirection);
}

void MeshLayer::InitializeLighting()
{
	{
		glEnable(GL_LIGHT0); glEnable(GL_LIGHT1); glEnable(GL_LIGHT2);
		glEnable(GL_LIGHT3); glEnable(GL_LIGHT4); glEnable(GL_LIGHT5);

		GLfloat light_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };

		GLfloat light0_diffuse[] = { 0.6f, 0.0f, 0.0f, 1.0f };
		GLfloat light1_diffuse[] = { 0.0f, 0.6f, 0.0f, 1.0f };
		GLfloat light2_diffuse[] = { 0.0f, 0.0f, 0.6f, 1.0f };
		GLfloat light3_diffuse[] = { 0.3f, 0.3f, 0.0f, 1.0f };
		GLfloat light4_diffuse[] = { 0.0f, 0.3f, 0.3f, 1.0f };
		GLfloat light5_diffuse[] = { 0.3f, 0.0f, 0.3f, 1.0f };

		GLfloat light0_specular[] = { 0.6f, 0.0f, 0.0f, 1.0f };
		GLfloat light1_specular[] = { 0.0f, 0.6f, 0.0f, 1.0f };
		GLfloat light2_specular[] = { 0.0f, 0.0f, 0.6f, 1.0f };
		GLfloat light3_specular[] = { 0.3f, 0.3f, 0.0f, 1.0f };
		GLfloat light4_specular[] = { 0.0f, 0.3f, 0.3f, 1.0f };
		GLfloat light5_specular[] = { 0.3f, 0.0f, 0.3f, 1.0f };

		float inf = (float)Config::Navigation::DEFAULT_FAR; 

		GLfloat light0_position[] = { inf, 0.0f, 0.0f, 1.0f };
		GLfloat light1_position[] = { 0.0f, inf, 0.0f, 1.0f };
		GLfloat light2_position[] = { 0.0f, 0.0f, inf, 1.0f };
		GLfloat light3_position[] = { -inf, 0.0f, 0.0f, 1.0f };
		GLfloat light4_position[] = { 0.0f, -inf, 0.0f, 1.0f };
		GLfloat light5_position[] = { 0.0f, 0.0f, -inf, 1.0f };

		GLfloat light0_spot_direction[] = { -1.0f, 0.0f, 0.0f };
		GLfloat light1_spot_direction[] = { 0.0f, -1.0f, 0.0f };
		GLfloat light2_spot_direction[] = { 0.0f, 0.0f, -1.0f };
		GLfloat light3_spot_direction[] = { 1.0f, 0.0f, 0.0f };
		GLfloat light4_spot_direction[] = { 0.0f, 1.0f, 0.0f };
		GLfloat light5_spot_direction[] = { 0.0f, 0.0f, 1.0f };

		InitializeLightEnum(GL_LIGHT0, 
							light_ambient, light0_diffuse, light0_specular, 
							light0_position, light0_spot_direction);
		InitializeLightEnum(GL_LIGHT1, 
							light_ambient, light1_diffuse, light1_specular, 
							light1_position, light1_spot_direction);
		InitializeLightEnum(GL_LIGHT2, 
							light_ambient, light2_diffuse, light2_specular, 
							light2_position, light2_spot_direction);
		InitializeLightEnum(GL_LIGHT3, 
							light_ambient, light3_diffuse, light3_specular, 
							light3_position, light3_spot_direction);
		InitializeLightEnum(GL_LIGHT4, 
							light_ambient, light4_diffuse, light4_specular, 
							light4_position, light4_spot_direction);
		InitializeLightEnum(GL_LIGHT5, 
							light_ambient, light5_diffuse, light5_specular, 
							light5_position, light5_spot_direction);
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

void MeshLayer::ClearCurrentEdge()
{
	if (m_pCurrentEdge != NULL)
	{
		delete m_pCurrentEdge->_pV0;
		delete m_pCurrentEdge->_pV1;
		delete m_pCurrentEdge;
		m_pCurrentEdge = NULL;
	}
}

void MeshLayer::ClearCurrentTriangle()
{
	if (m_pCurrentTriangle != NULL)
	{
		delete m_pCurrentTriangle->_pV0;
		delete m_pCurrentTriangle->_pV1;
		delete m_pCurrentTriangle->_pV2;
		delete m_pCurrentTriangle;
		m_pCurrentTriangle = NULL;
	}
}

void MeshLayer::UpdateCurrentEdge( edge& e, points_type& points )
{
	ClearCurrentEdge();

	IMesh::UI::MeshHelper helper(m_pAdjuster);
	point& p0 = points[e.idx_i];
	point& p1 = points[e.idx_j];
	
	Vertex* pV0 = helper.CreateVertexFromPoint(p0);
	pV0->m_id = e.idx_i;
	Vertex* pV1 = helper.CreateVertexFromPoint(p1);
	pV1->m_id = e.idx_j;

	Edge* pE = helper.CreateEdgeFromVertex(pV0, pV1);
	pE->m_color = Colors::RED;
	pE->m_lineWidth = 2;
	m_pCurrentEdge = pE;
}

void MeshLayer::UpdateCurrentTriangle( triangle& t, points_type& points )
{
	ClearCurrentTriangle();

	IMesh::UI::MeshHelper helper(m_pAdjuster);
	
	point& p0 = points[t.idx_i];
	point& p1 = points[t.idx_j];
	point& p2 = points[t.idx_k];
	
	Vertex* pV0 = helper.CreateVertexFromPoint(p0);
	pV0->m_id = t.idx_i;
	Vertex* pV1 = helper.CreateVertexFromPoint(p1);
	pV1->m_id = t.idx_j;
	Vertex* pV2 = helper.CreateVertexFromPoint(p2);
	pV2->m_id = t.idx_k;

	Triangle* pT = helper.CreateTriangleFromVertex(pV0, pV1, pV2);
	pT->m_fill = Colors::YELLOW;
	m_pCurrentTriangle = pT;
}

void MeshLayer::UpdateSpherePos(point3D& center, float radius)
{
	Num::Vec3f pos = m_pAdjuster->Adjust((float)center.x, (float)center.y, (float)center.z);
	m_sphere.m_pos = pos;
	m_sphere.m_radius = radius * m_pAdjuster->m_scaleRate;
}

} } }
