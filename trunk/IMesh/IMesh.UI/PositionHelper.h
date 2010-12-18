#pragma once

#include "Structures.h"

namespace IMesh { namespace UI { // namespace IMesh::UI

using namespace IMesh::Num::GL;

class PositionHelper
{
public:
	/*static PosVec3d Orth2Sphere(const PosVec3d& v) {
		PosVec3d orth;
		return orth;
	}*/

	static PosVec3d Sphere2Orth(const PosVec3d& v);

	static PosVec3d SphereFindTopOrth(const PosVec3d& v);
};

} }
