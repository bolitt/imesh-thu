#include "StdAfx.h"
#include "Vertex.h"

namespace IMesh { namespace UI { namespace Models { 

using namespace IMesh::UI::Config;

const static Vertex::id_type UNINITIALIZED_ID = -1;
const static float DETAULT_POINTSIZE = 2.0f;
const static Vertex::color_type DEFAULT_COLOR = Colors::RED;


Vertex::Vertex(void) : m_id(UNINITIALIZED_ID),
					   m_pointSize(DETAULT_POINTSIZE),
					   m_color(DEFAULT_COLOR)
{
	
}


Vertex::~Vertex(void)
{
}

void Vertex::OnRender()
{
	if (!m_IsVisible) return;

	glPointSize(m_pointSize);
	glBegin(GL_POINTS);
	{
		glColor3fv(m_color.ConstPtr());
		glVertex3fv(m_pos.ConstPtr());
	}
	glEnd();
	glPointSize(1);
	_DEBUG_ONRENDER_CHECK_ERROR_();
}

} } }
