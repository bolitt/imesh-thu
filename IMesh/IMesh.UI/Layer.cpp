#include "StdAfx.h"
#include "Layer.h"

namespace IMesh { namespace UI { namespace Models {

Layer::Layer(void)
{
}


Layer::~Layer(void)
{
}

void Layer::OnRender()
{
	if (!m_IsVisible) return;
	
	parent_type::OnRender();
}

} } }