#pragma once
#include "stdafx.h"
#include <vector>


//#define GL_NO_ERROR                       0
//#define GL_INVALID_ENUM                   0x0500
//#define GL_INVALID_VALUE                  0x0501
//#define GL_INVALID_OPERATION              0x0502
//#define GL_STACK_OVERFLOW                 0x0503
//#define GL_STACK_UNDERFLOW                0x0504
//#define GL_OUT_OF_MEMORY                  0x0505

#ifdef _DEBUG
#define _DEBUG_ONRENDER_CHECK_ERROR_()  do { GLenum err = glGetError(); if (GL_NO_ERROR != err) { TRACE1("OpenGLError: %s", gluErrorStringWIN(err)); ASSERT(GL_NO_ERROR == err);  } } while(0)
#else
  #define _DEBUG_ONRENDER_CHECK_ERROR_()
#endif

namespace IMesh { namespace UI { namespace Models {

class IRenderable
{
public:
	virtual void OnRender() = 0;
};


class Model : public IRenderable
{
public:
	typedef  Model     base_type;
	typedef  Model     parent_type;
	typedef  Model     self_type;
	
public:
	Model();
	virtual ~Model();
	
public:
	void OnRender();
	virtual void OnSetup();
	virtual void OnDestroy();
};


class ModelCollection : public Model
{
public:
	typedef  std::vector<Model*>  children_type;
	typedef  Model                parent_type;
	typedef  ModelCollection      self_type;
	
public:
	children_type m_children;

public:
	void OnRender();
};


} } } ///:~ IMesh::UI::Models

