#pragma once

#include "Structures.h"

namespace IMesh { namespace UI { namespace Models {

class ModelViewAdjuster
{
public:
	ModelViewAdjuster(void);
	~ModelViewAdjuster(void);

	// For Model:
	float m_translateX;
	float m_translateY;
	float m_translateZ;
	float m_scaleRate;

	Num::Vec3f m_lowest;
	Num::Vec3f m_highest;
public:
	void Initialize(Num::Vec3f& lowest, Num::Vec3f& highest);
	Num::Vec3f Adjust(Num::Vec3f& v);
	Num::Vec3f Adjust(float x, float y, float z);
};

} } }
