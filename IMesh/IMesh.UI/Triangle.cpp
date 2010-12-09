#include "StdAfx.h"
#include "Triangle.h"

namespace IMesh { namespace UI { namespace Models { 

Triangle::Triangle()
{
}


Triangle::~Triangle()
{
}

void Triangle::OnRender()
{
	parent_type::OnRender();

	struct Tester
	{
		static void Test()
		{
			using namespace Config;
			//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			//glEnable(GL_DEPTH_TEST);
			//glEnable(GL_CULL_FACE);
			glBegin(GL_POLYGON);
			{
				glColor3fv(Colors::RED.ConstPtr());
				glVertex3f(100.0f, 20.0f, 0.0f);
				glColor3fv(Colors::GREEN.ConstPtr());
				glVertex3f(20.0f, 20.0f, 0.0f);
				glColor3fv(Colors::BLUE.ConstPtr());
				glVertex3f(20.0f, 100.0f, 0.0f);
			}
			glEnd();
			_DEBUG_ONRENDER_CHECK_ERROR_();
		}
	};
		
	Tester::Test();
}

} } }
