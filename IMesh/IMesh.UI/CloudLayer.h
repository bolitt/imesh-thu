#pragma once

#include "Layer.h"

#include "Axis.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Vertex.h"
#include "Edge.h"

namespace IMesh { namespace UI { namespace Models {

class CloudLayer : public Layer
{
public:
	typedef  Layer			parent_type;
	typedef  CloudLayer		self_type;

public:
	std::vector<Vertex*> m_vertiesHolder;
	std::vector<Edge*> m_edgesHolder;

public:
	CloudLayer(void);
	~CloudLayer(void);

	void ClearLayer();
	void SetLayer(CloudInit& cloud);

};

} } }
