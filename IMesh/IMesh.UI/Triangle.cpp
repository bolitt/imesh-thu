#include "StdAfx.h"
#include "Triangle.h"

namespace IMesh { namespace UI { namespace Models { 

using namespace IMesh::UI::Config;

const static Triangle::id_type UNINITIALIZED_ID = -1;
const static Triangle::color_type DEFAULT_FILL = Colors::WHITE;

Triangle::Triangle() : m_id(UNINITIALIZED_ID), 
						m_fill(DEFAULT_FILL)
{
}


Triangle::~Triangle()
{
}

void Triangle::OnRender()
{
	if (!m_IsVisible) return;

	parent_type::OnRender();

	{
		using namespace Config;
		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		//glEnable(GL_DEPTH_TEST);
		//glEnable(GL_CULL_FACE);
		ASSERT(_pV0 != NULL && _pV1 !=NULL && _pV2 != NULL);
		glBegin(GL_TRIANGLES);
		{
			glColor3fv(m_fill.ConstPtr());
			
			Num::Vec3f& v10 = _pV1->m_pos - _pV0->m_pos;
			Num::Vec3f& v21 = _pV2->m_pos - _pV1->m_pos;
			Num::Vec3f& nVec = v10.Cross(v21);
			nVec.Normalize();
			glNormal3fv(nVec.ConstPtr());
			
			glVertex3fv(_pV0->m_pos.ConstPtr());
			glVertex3fv(_pV1->m_pos.ConstPtr());
			glVertex3fv(_pV2->m_pos.ConstPtr());
		}
		glEnd();
		_DEBUG_ONRENDER_CHECK_ERROR_();
	}
}

} } }
