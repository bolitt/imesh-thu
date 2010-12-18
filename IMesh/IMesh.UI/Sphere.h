#pragma once

#include "IModel.h"

namespace IMesh { namespace UI { namespace Models { 

class Sphere : public Model
{
public:
	typedef  Model		parent_type;
	typedef  Sphere		self_type;
	typedef	 Num::Vec3f		value_type;

protected:
	GLUquadric*		m_pQuadric;

public:
	int m_slices;
	int m_stacks;
	float m_radius;
	union {
		struct {
			value_type		m_pos;
		};
		struct {
			value_type		m_val;
		};
	};

public:
	Sphere();
	~Sphere();

	void OnRender();
	void OnSetup();
};

} } }
