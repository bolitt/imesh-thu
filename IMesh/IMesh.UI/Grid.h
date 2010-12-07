#pragma once

#include "IModel.h"

namespace IMesh { namespace UI { namespace Models {

class Grid : public Model
{
public:
	float m_size;
	float m_step;

public:
	Grid(void);
	~Grid(void);
	
	void OnRender(); // override
};

}}}
