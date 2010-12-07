#include "StdAfx.h"
#include "Camera.h"



namespace IMesh { namespace UI {

using namespace IMesh::UI::Config::Navigation;

Camera::Camera(void) : m_angleX(DEFAULT_ANGLE_X), 
					m_angleY(DEFAULT_ANGLE_Y), 
					m_distance(DEFAULT_DISTANCE),
					m_minDistance(DEFAULT_MIN_DISTANCE),
					m_maxDistance(DEFAULT_MAX_DISTANCE)
{

}


Camera::~Camera(void)
{
}

PosVec3d Camera::ToPolarVec3()
{
	PosVec3d polar(m_angleX * DEG2RAD, m_angleY * DEG2RAD, m_distance);
	return polar;
}

void Camera::Zoom( ZoomType z )
{
	double delta = 1.0;
	if (z == Camera::CAMERA_ZOOM_IN ) {
		delta = ZOOM_IN_RATE;
	} else if (z == Camera::CAMERA_ZOOM_OUT) {
		delta = ZOOM_OUT_RATE;
	}
	double dist = m_distance * delta;
	dist = (dist > m_minDistance ? dist : m_minDistance);
	dist = (dist < m_maxDistance ? dist : m_maxDistance);
	m_distance = dist;
}

void Camera::Rotate(double rotateX, double rotateY)
{
	m_angleX += rotateX;
	m_angleY += rotateY;
}

}}