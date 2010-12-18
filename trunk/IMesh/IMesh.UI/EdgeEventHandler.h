#pragma once


#include "Structures.h"
#include "Camera.h"
#include "MeshLayer.h"
#include "Triangle.h"
#include "Vertex.h"
#include "Edge.h"


namespace IMesh { namespace UI {

class CVisualizer;

class EdgeEventListener : public IMesh::Interface::EventListener
{
protected:
	typedef IMesh::UI::Models::MeshLayer layer_type;
	typedef vector<triangle* > triangle_list_type;
	typedef vector<point> points_type;

protected:
	IMesh::UI::CVisualizer* m_pVisualizer;
	layer_type* m_pDemoLayer;
	std::vector<IMesh::UI::Models::Vertex *> m_verticesHolder;
	std::vector<IMesh::UI::Models::Edge *>   m_edgesHolder;
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
