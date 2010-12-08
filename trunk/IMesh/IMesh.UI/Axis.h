#pragma once
#include "IModel.h"

namespace IMesh { namespace UI { namespace Models {

class Axis : public Model
{
public:
	typedef  Model	parent_type;
	typedef  Axis	self_type;

public:
	float m_size;

	bool m_isXEnabled;
	bool m_isYEnabled;
	bool m_isZEnabled;

public:
	Axis(void);
	~Axis(void);

	void OnRender();
};

}}}
