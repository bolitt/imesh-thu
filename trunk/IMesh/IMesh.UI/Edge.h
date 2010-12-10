#pragma once

#include "IModel.h"
#include "Vertex.h"

namespace IMesh { namespace UI { namespace Models {

class Edge : public Model
{
public:
	typedef		Model				parent_type;
	typedef		Edge				self_type;
	typedef		Vertex				vertex_type;
	typedef		int					id_type;
	typedef		Num::GL::RGBColor	color_type;

public:
	union {
		vertex_type* _pVals[2];
		struct  
		{
			vertex_type* _pV0;
			vertex_type* _pV1;
		};
	};
	id_type		m_id;
	color_type	m_color;
	float		m_lineWidth;


public:
	Edge(void);
	~Edge(void);
	void OnRender();
};

} } }
