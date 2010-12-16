#pragma once

#include "../IMesh.Share/vec.h"
#include "../IMesh.Norm/Cloud.h"
#include "TriangulationHandler.h"
#include "predefs.h"


#ifdef _DEBUG
  #pragma comment(lib, "../Debug/IMesh.Norm.lib")
#else
  #pragma comment(lib, "../Release/IMesh.Norm.lib")
#endif

namespace IMesh { namespace UI {

class CloudInit
{
public:
	Norm::Cloud m_cloud;	
	TriangulationHandler m_triangleHandler;

public:
	CloudInit(void);
	CloudInit(char*);
	~CloudInit(void);


	void Initialize();
	//std::vector<Num::Vec3f> GetPoints();
	//std::vector<Num::Vec3f> GetNorms();
	std::vector<point3D> GetPoints();
	std::vector<vect> GetNorms();
};

} } 
