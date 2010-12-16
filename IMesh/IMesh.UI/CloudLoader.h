#pragma once

#include "Structures.h"

namespace IMesh { namespace UI {

class CloudLoader
{
public:
	Norm::Cloud m_cloud;

public:
	CloudLoader(void);
	~CloudLoader(void);

	void Initialize();
	std::vector<Num::Vec3f> GetPoints();
	std::vector<Num::Vec3f> GetNorms();
};

} } 
