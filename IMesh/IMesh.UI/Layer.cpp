#include "StdAfx.h"
#include "Layer.h"

namespace IMesh { namespace UI { namespace Models {

Layer::Layer(void) : m_IsVisible(true)
{
}


Layer::~Layer(void)
{
}

void Layer::OnRender()
{
	if (m_IsVisible) 
	{
		parent_type::OnRender();
	}
}

} } }