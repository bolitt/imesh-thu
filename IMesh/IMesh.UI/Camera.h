#pragma once

#include "Config.h"
#include "Structures.h"
#include "PositionHelper.h"

namespace IMesh { namespace UI {

typedef Num::GL::PosVec3d  PosVec3d;

class Camera
{
public:
	

public:
	enum ZoomType 
	{ 
		CAMERA_ZOOM_IN = 0,
		CAMERA_ZOOM_OUT = 1
	};

public:
	Camera(void);
	~Camera(void);

public:
	double m_angleX;
	double m_angleY;
	double m_distance;

	double m_minDistance;
	double m_maxDistance;

	PosVec3d ToPolarVec3();
	void Zoom(ZoomType z);
	void Rotate(double rotateX, double rotateY);

};

}}