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
	~CloudInit(void);

	void Initialize();
	void Initialize(char* file);
	void RunTriangulate();

	std::vector<Num::Vec3f> GetPoints();
	std::vector<Num::Vec3f> GetNorms();

	Num::Vec3f GetLowestDim();
	Num::Vec3f GetHighestDim();
	Num::Vec3f GetMiddleDim();
	/*std::vector<point3D> GetPoints();
	std::vector<vect> GetNorms();*/
};

} } 
