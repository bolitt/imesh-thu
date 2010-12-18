#include "StdAfx.h"
#include "PositionHelper.h"

namespace IMesh { namespace UI { // namespace IMesh::UI


PosVec3d PositionHelper::Sphere2Orth( const PosVec3d& v )
{
	PosVec3d orth;
	GLdouble smallRadius = v._radius * sin(v._coLatitude);
	orth._x = smallRadius * cos(v._longtitude);
	orth._y = smallRadius * sin(v._longtitude);
	orth._z = v._radius * cos(v._coLatitude);
	return orth;
}

PosVec3d PositionHelper::SphereFindTopOrth( const PosVec3d& v )
{
	PosVec3d topSphere = v;
	topSphere._coLatitude -= M_PI_2;
	PosVec3d topOrth = Sphere2Orth(topSphere);
	return topOrth;
}

} }
