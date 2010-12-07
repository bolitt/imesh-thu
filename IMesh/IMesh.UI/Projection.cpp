#include "StdAfx.h"
#include "Projection.h"


namespace IMesh { namespace UI {

using namespace IMesh::UI::Config::Navigation;

Projection::Projection(void) : m_left(DEFAULT_LEFT), m_right(DEFAULT_RIGHT), 
							m_bottom(DEFAULT_BOTTOM), m_top(DEFAULT_TOP), 
							m_zNear(DEFAULT_NEAR), m_zFar(DEFAULT_FAR)
{
}


Projection::~Projection(void)
{
}


void Projection::Reshape(double width, double height) 
{
	double ratio = (height > 0) ? width / height : 1;
	m_left = - DEFAULT_BASELINE * ratio;
	m_right = DEFAULT_BASELINE * ratio;
	m_bottom = - DEFAULT_BASELINE;
	m_top = DEFAULT_BASELINE;
}


}}