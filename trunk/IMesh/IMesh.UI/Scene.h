#pragma once

#include "IModel.h"
#include "Layer.h"
#include "CloudLayer.h"
#include "MeshLayer.h"

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
	CloudLayer m_cloudLayer;
	MeshLayer m_meshLayer;

	Grid m_worldGrid;
	Axis m_worldAxis;

	// For Model:
	ModelViewAdjuster m_adjuster;

public:
	Scene(void);
	~Scene(void);
	void OnSetup();
	void OnRender();

	void InitializeLighting();
};

} } }

