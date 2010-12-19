#include "StdAfx.h"
#include "Sphere.h"
#include "Config.h"

namespace IMesh { namespace UI { namespace Models {

const static int DEFAULT_SLICES = 36;
const static int DEFAULT_STACKS = 36;
const static float DEFAULT_RADIUS = 10.0f;

Sphere::Sphere(void)
{
	m_pQuadric = NULL;
	m_slices = DEFAULT_SLICES;
	m_stacks = DEFAULT_STACKS;
	m_radius = DEFAULT_RADIUS;

}


Sphere::~Sphere(void)
{
	if (m_pQuadric != NULL) {
		gluDeleteQuadric(m_pQuadric);
		m_pQuadric = NULL;
	}
}

void Sphere::OnSetup()
{
	if (m_pQuadric == NULL) {
		m_pQuadric = gluNewQuadric();
		gluQuadricDrawStyle(m_pQuadric, GLU_FILL);
	}
}


void Sphere::OnRender()
{
	if (!m_IsVisible) return;

	parent_type::OnRender();

	using namespace Config;
	{
		glPushMatrix();
		glTranslatef(m_pos._x, m_pos._y, m_pos._z);
		glColor3fv(Colors::WHITE.ConstPtr());	
		gluSphere(m_pQuadric, m_radius, m_slices, m_stacks); // why this cause INVALID_OPERATION_ERROR
		glPopMatrix();
	}
	_DEBUG_ONRENDER_CHECK_ERROR_();	
}

} } }
