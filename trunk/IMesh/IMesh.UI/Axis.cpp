#include "StdAfx.h"
#include "Axis.h"


namespace IMesh { namespace UI { namespace Models {

Axis::Axis(void)
{
	m_size = 100;
	m_isXEnabled = m_isYEnabled = m_isZEnabled = true;
}


Axis::~Axis(void)
{
}

void Axis::OnRender()
{
	if (!m_IsVisible) return;

	parent_type::OnRender();

	float size = m_size;

	GLboolean bGL_LIGHTING = glIsEnabled(GL_LIGHTING);
	glDepthFunc(GL_ALWAYS);     // to avoid visual artifacts with grid lines
	glDisable(GL_LIGHTING);

	// draw axis
	glLineWidth(3);
	glBegin(GL_LINES);
	{
		// X-axis
		if (m_isXEnabled) {
			glColor3f(1, 0, 0);
			glVertex3f(0, 0, 0);
			glVertex3f(size, 0, 0);
		}
		// Y-axis
		if (m_isYEnabled) {
			glColor3f(0, 1, 0);
			glVertex3f(0, 0, 0);
			glVertex3f(0, size, 0);
		}
		// Z-axis
		if (m_isZEnabled) {
			glColor3f(0, 0, 1);
			glVertex3f(0, 0, 0);
			glVertex3f(0, 0, size);
		}
	}
	glEnd();
	_DEBUG_ONRENDER_CHECK_ERROR_();

	glLineWidth(1);
	// draw arrows(actually big square dots)
	glPointSize(4);
	glBegin(GL_POINTS);
	{
		if (m_isXEnabled) {
			glColor3f(1, 0, 0);
			glVertex3f(size, 0, 0);
		}
		if (m_isYEnabled) {
			glColor3f(0, 1, 0);
			glVertex3f(0, size, 0);
		}
		if (m_isZEnabled) {
			glColor3f(0, 0, 1);
			glVertex3f(0, 0, size);
		}

	}
	glEnd();
	glPointSize(1);
	_DEBUG_ONRENDER_CHECK_ERROR_();

	// restore default settings
	if (bGL_LIGHTING) { glEnable(GL_LIGHTING); }
	glDepthFunc(GL_EQUAL);
}



}}}
