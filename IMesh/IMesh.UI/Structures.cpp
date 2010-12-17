#include "stdafx.h"
#include "Structures.h"


#ifdef _DEBUG
#pragma comment(lib, "../Debug/IMesh.Norm.lib")
#pragma comment(lib, "../Debug/IMesh.Share.lib")
#pragma comment(lib, "../Debug/IMesh.Triangulate.lib")
#else
#pragma comment(lib, "../Release/IMesh.Norm.lib")
#pragma comment(lib, "../Release/IMesh.Share.lib")
#pragma comment(lib, "../Release/IMesh.Triangulate.lib")
#endif