#pragma once

#include "IModel.h"
#include "Layer.h"
#include "Grid.h"
#include "Axis.h"

namespace IMesh { namespace UI { namespace Models {

class Scene : public Model
{
public:
	typedef  Model  parent_type;
	typedef  Scene  self_type;

public:
	Layer m_baseLayer;
	Layer m_overLayer;

	// m_baseLayer Children:
	Grid m_worldGrid;
	Axis m_worldAxis;

	// m_overLayer Children:

public:
	Scene(void);
	~Scene(void);
	void Initialize();
	void OnRender();
};

} } }

