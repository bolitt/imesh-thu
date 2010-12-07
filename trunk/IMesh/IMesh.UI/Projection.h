#pragma once

#include "Config.h"

namespace IMesh { namespace UI {

class Projection
{
public:
	Projection(void);
	~Projection(void);
	void Reshape(double width, double height);

public:
	double m_left;
	double m_right;
	double m_bottom;
	double m_top;
	double m_zNear;
	double m_zFar;

};

}}

