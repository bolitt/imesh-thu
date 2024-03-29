#pragma once

#include "Layer.h"

#include "Axis.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Vertex.h"
#include "Edge.h"
#include "ModelViewAdjuster.h"

namespace IMesh { namespace UI { namespace Models {

class MeshLayer : public Layer
{
public:
	typedef  Layer		parent_type;
	typedef  MeshLayer	self_type;

protected:
	typedef vector<triangle* > triangle_list_type;
	typedef vector<point> points_type;

public:
	Sphere m_sphere;
	Triangle m_triangle;

	std::vector<Vertex *> m_verticesHolder;
	std::vector<Edge *>   m_edgesHolder;
	std::vector<Triangle *> m_trianglesHolder;
	Layer		m_verticesLayer;
	Layer		m_edgesLayer;
	Layer		m_trianglesLayer;


	Edge*		m_pCurrentEdge;
	Triangle*	m_pCurrentTriangle;

	ModelViewAdjuster* m_pAdjuster;

public:
	MeshLayer(void);
	~MeshLayer(void);
	void OnSetup();
	void OnRender();
	void InitializeLightEnum(GLenum lightEnum, 
							GLfloat* ambient, GLfloat* diffuse, GLfloat* specular, 
							GLfloat* position, GLfloat* spotDirection );
	void InitializeLighting();

	void ClearLayer();
	void UpdateLayer( triangle_list_type &triangles, points_type& points );
	
	void ClearCurrentEdge();
	void UpdateCurrentEdge(edge& e, points_type& points);

	void ClearCurrentTriangle();
	void UpdateCurrentTriangle(triangle& t, points_type& points);

	void UpdateSpherePos(point3D& center, float radius);
};

} } }


