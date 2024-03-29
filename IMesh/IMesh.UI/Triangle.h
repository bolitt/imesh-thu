#pragma once

#include "Structures.h"
#include "IModel.h"
#include "Vertex.h"
#include "Config.h"

namespace IMesh { namespace UI { namespace Models { 

class Triangle : public Model
{
public:
	typedef		Model				parent_type;
	typedef		Triangle			self_type;
	typedef		Vertex				vertex_type;
	typedef		int					id_type;
	typedef		Num::GL::RGBColor	color_type;

public:
	union {
		vertex_type* _pVals[3];
		struct  
		{
			vertex_type* _pV0;
			vertex_type* _pV1;
			vertex_type* _pV2;
		};
	};
	id_type		m_id;
	color_type	m_fill;

public:
	Triangle();
	~Triangle();
	void OnRender();
};

} } }