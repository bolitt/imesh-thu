#pragma once

#include "IModel.h"

namespace IMesh { namespace UI { namespace Models {

class Layer : public ModelCollection
{
public:
	typedef  ModelCollection   parent_type;
	typedef  Layer			   self_type;

public:
	bool m_IsVisible;

public:
	Layer(void);
	~Layer(void);
	void OnRender();
};

} } }

