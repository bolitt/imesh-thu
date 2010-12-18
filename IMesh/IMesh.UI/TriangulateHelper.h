#pragma once

#include "Structures.h"
#include "Vertex.h"
#include "Edge.h"
#include "Triangle.h"

namespace IMesh { namespace UI {

using namespace IMesh::UI::Models;

class TriangularHelper
{
public:
	Vertex* CreateVertexFromPoint(point& p);
	Triangle* CreateTriangleFromVertex(Vertex* pV0, Vertex* pV1, Vertex* pV2);
	Edge* CreateEdgeFromVertex(Vertex* pV0, Vertex* pV1);
};

} }