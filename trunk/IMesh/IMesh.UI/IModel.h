#pragma once

#include <vector>

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
	void OnRender();
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

