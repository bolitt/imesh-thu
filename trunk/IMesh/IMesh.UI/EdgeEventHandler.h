#pragma once

#include "../IMesh.Triangulate/EventCommon.h"
#include "../IMesh.Triangulate/predefs.h"
#include "../IMesh.Triangulate/EdgePivot.h"
#include "../IMesh.Triangulate/TriangulationHandler.h"
#include "../IMesh.Triangulate/SeedSelection.h"
#include "Structures.h"
#include "Camera.h"
#include "Layer.h"
#include "Triangle.h"
#include "Vertex.h"

#ifdef _DEBUG
  #pragma comment(lib, "../Debug/IMesh.Share.lib")
  #pragma comment(lib, "../Debug/IMesh.Triangulate.lib")
#else
  #pragma comment(lib, "../Release/IMesh.Share.lib")
  #pragma comment(lib, "../Release/IMesh.Triangulate.lib")
#endif


namespace IMesh { namespace UI {

class CVisualizer;

class EdgeEventListener : public IMesh::Interface::EventListener
{
public:
	typedef IMesh::UI::Models::Layer layer_type;

protected:
	IMesh::UI::CVisualizer* m_pVisualizer;
	layer_type* m_pDemoLayer;
	std::vector<IMesh::UI::Models::Vertex *> m_verticesHolder;
	std::vector<IMesh::UI::Models::Triangle *> m_trianglesHolder;

protected:
	void UpdateLayer(edge& newEdge, EdgeEventArg& edgeEventArg);
	void Clear();

public:
	void Initialize(IMesh::UI::CVisualizer* pVisualizer, layer_type* pDemoLayer);

	void OnHandle(void* source, const IMesh::Interface::EventArg& eventArgs);
	
public:
	EdgeEventListener();
	~EdgeEventListener();	
};

} } 
