#include "StdAfx.h"
#include "Edge.h"

namespace IMesh { namespace UI { namespace Models {

using namespace IMesh::UI::Config;

const static Edge::id_type UNINITIALIZED_ID = -1;
const static float DEFAULT_LINE_WIDTH = 1.0f;
const static Edge::color_type DEFAULT_COLOR = Colors::WHITE;

Edge::Edge() : m_id(UNINITIALIZED_ID),
			   m_lineWidth(DEFAULT_LINE_WIDTH),
			   m_color(DEFAULT_COLOR)
{
}


Edge::~Edge()
{
	
}

void Edge::OnRender()
{
	if (!m_IsVisible) return;

	glLineWidth(m_lineWidth);
	glBegin(GL_LINES);
	{
		glColor3fv(m_color.ConstPtr());
		glVertex3fv(_pV0->m_pos.ConstPtr());
		glVertex3fv(_pV1->m_pos.ConstPtr());
	}
	glEnd();
	glLineWidth(1);
	_DEBUG_ONRENDER_CHECK_ERROR_();
}

} } }
