#pragma once

#include <gl/gl.h> 
#include <gl/glu.h>
#include "../IMesh.Share/vec.h"
#include "../IMesh.Norm/Cloud.h"
#include "../IMesh.Triangulate/CloudInit.h"
#include "../IMesh.Triangulate/EventCommon.h"
#include "../IMesh.Triangulate/predefs.h"
#include "../IMesh.Triangulate/EdgePivot.h"
#include "../IMesh.Triangulate/TriangulationHandler.h"
#include "../IMesh.Triangulate/SeedSelection.h"


namespace IMesh { namespace Num { namespace GL {
	//typedef unsigned int GLenum;
	//typedef unsigned char GLboolean;
	//typedef unsigned int GLbitfield;
	//typedef signed char GLbyte;
	//typedef short GLshort;
	//typedef int GLint;
	//typedef int GLsizei;
	//typedef unsigned char GLubyte;
	//typedef unsigned short GLushort;
	//typedef unsigned int GLuint;
	//typedef float GLfloat;
	//typedef float GLclampf;
	//typedef double GLdouble;
	//typedef double GLclampd;
	//typedef void GLvoid;

	typedef Num::Vec3<GLboolean> Vec3GLboolean;
	typedef Num::Vec3<GLbitfield> Vec3GLbitfield;
	typedef Num::Vec3<GLbyte> Vec3GLbyte;
	typedef Num::Vec3<GLshort> Vec3GLshort;
	typedef Num::Vec3<GLint> Vec3GLint;
	typedef Num::Vec3<GLubyte> Vec3GLubyte;
	typedef Num::Vec3<GLushort> Vec3GLushort;
	typedef Num::Vec3<GLuint> Vec3GLuint;
	typedef Num::Vec3<GLfloat> Vec3GLfloat;
	typedef Num::Vec3<GLdouble> Vec3GLdouble;
	
	typedef Num::Vec3<GLfloat> RGBColor;
	typedef Vec3GLdouble PosVec3d;
} } }

