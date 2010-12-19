#include "StdAfx.h"
#include "Grid.h"

namespace IMesh { namespace UI { namespace Models {

Grid::Grid(void)
{
	m_size = 80;
	m_step = 5;
}

Grid::~Grid(void)
{
}

void Grid::OnRender()
{
	if (!m_IsVisible) return;

	parent_type::OnRender();

	float step = m_step, 
		  size = m_size;
	GLboolean bGL_LIGHTING = glIsEnabled(GL_LIGHTING);
	// disable lighting
	glDisable(GL_LIGHTING);

	
	glBegin(GL_LINES);
	{
		glColor3f(0.3f, 0.3f, 0.3f);
		for(float i=step; i <= size; i+= step)
		{
			glVertex3f(-size, i, 0);   // lines parallel to X-axis
			glVertex3f( size, i, 0);
			glVertex3f(-size, -i, 0);   // lines parallel to X-axis
			glVertex3f( size, -i, 0);

			glVertex3f( i, -size, 0);   // lines parallel to Y-axis
			glVertex3f( i, size, 0);
			glVertex3f(-i, -size, 0);   // lines parallel to Y-axis
			glVertex3f(-i, size, 0);
		}

		// x-axis
		glColor3f(0.5f, 0, 0);
		glVertex3f(-size, 0, 0);
		glVertex3f( size, 0, 0);

		// Y-axis
		glColor3f(0, 0.5f, 0);
		glVertex3f(0, -size, 0);
		glVertex3f(0, size,  0);
	}
	glEnd();
	_DEBUG_ONRENDER_CHECK_ERROR_();

	// enable lighting back
	if (bGL_LIGHTING) { glEnable(GL_LIGHTING); }
}

}}}