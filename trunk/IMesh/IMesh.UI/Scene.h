#pragma once

#include "IModel.h"
#include "Layer.h"
#include "Grid.h"

#include "Axis.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Vertex.h"
#include "Edge.h"

#include "CloudLoader.h"

namespace IMesh { namespace UI { namespace Models {

class Scene : public Model
{
public:
	typedef  Model  parent_type;
	typedef  Scene  self_type;

public:
	Layer m_baseLayer;
	Layer m_overLayer;
	Layer m_demoLayer;

	// m_baseLayer Children:
	Grid m_worldGrid;
	Axis m_worldAxis;

	// m_overLayer Children:
	Sphere m_sphere;
	Triangle m_triangle;
	std::vector<Vertex*> m_verties;
	std::vector<Edge*> m_edges;

	// m_demotLayer Children:


public:
	Scene(void);
	~Scene(void);
	void OnSetup(CloudInit& loader);
	void OnRender();

};

} } }

