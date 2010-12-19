Vec3f
Vec3f
#include "StdAfx.h"
#include "Config.h"
#include "ModelViewAdjuster.h"

namespace IMesh { namespace UI { namespace Models {

ModelViewAdjuster::ModelViewAdjuster(void)
{
	m_scaleRate = 1;
	m_translateX = m_translateY = m_translateZ = 0;
}


ModelViewAdjuster::~ModelViewAdjuster(void)
{
}

void ModelViewAdjuster::Initialize( Num::Vec3f& lowest, Num::Vec3f& highest )
{
	using namespace IMesh::UI::Config;
	float viewSize = (float)Navigation::DEFAULT_MODEL_VIEW_SIZE;
	
	m_lowest = lowest;
	m_highest = highest;

	float dx = (highest._x - lowest._x);
	float dy = (highest._y - lowest._y);
	float dz = (highest._z - lowest._z);
	m_translateX = - (dx / 2.0f);
	m_translateY = - (dy / 2.0f);
	m_translateZ = - (dz / 2.0f);
	
	float sx = highest._x + lowest._x;
	float sy = highest._y + lowest._y;
	float sz = highest._z + lowest._z;
	
	float sMax = max(max(sx, sy), sz);
	m_scaleRate = viewSize / sMax;
}

Num::Vec3f ModelViewAdjuster::Adjust(Num::Vec3f& v)
{
	return Adjust(v._x, v._y, v._z);
}

Num::Vec3f ModelViewAdjuster::Adjust( float x, float y, float z )
{
	Num::Vec3f& newV = Num::Vec3f(x + m_translateX, 
									y + m_translateY,
									z + m_translateZ);
	newV.Mul(m_scaleRate);
	return newV;
}


} } }

