#pragma once

#include "Layer.h"

#include "Axis.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Vertex.h"
#include "Edge.h"


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

public:
	MeshLayer(void);
	~MeshLayer(void);
	void OnSetup();
	void UpdateLayer( triangle_list_type &triangles, points_type& points );
	void ClearLayer();
	void OnRender();
};

} } }


