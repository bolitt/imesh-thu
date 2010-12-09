#pragma once

#include "Structures.h"
#include "IModel.h"

namespace IMesh { namespace UI { namespace Models { 

class Vertex : Model
{
public:
	typedef		Model				parent_type;
	typedef		Vertex				self_type;
	typedef		Num::Vec3f			value_type;
	typedef		unsigned int		id_type;

public:
	id_type			m_id;

public:
	Vertex();
	~Vertex();

public:
	void OnRender();
};

} } }
