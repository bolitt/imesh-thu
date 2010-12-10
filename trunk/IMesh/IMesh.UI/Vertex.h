#pragma once

#include "Structures.h"
#include "IModel.h"

namespace IMesh { namespace UI { namespace Models { 

class Vertex : public Model
{
public:
	typedef		Model				parent_type;
	typedef		Vertex				self_type;
	typedef		Num::Vec3f			value_type;
	typedef		int					id_type;
	typedef		Num::GL::RGBColor	color_type;

public:
	union {
		struct {
			value_type		m_pos;
		};
		struct {
			value_type		m_val;
		};
	};
	
	id_type			m_id;
	color_type		m_color;
	float			m_pointSize;

public:
	Vertex();
	~Vertex();

public:
	void OnRender();
};

} } }
