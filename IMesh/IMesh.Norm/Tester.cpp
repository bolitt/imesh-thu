#include <iostream>

static char THIS_FILE[] = __FILE__;

#include "ReadFile.h"

extern vector<Vector3> vertices,norm;

namespace IMesh { //: namespace IMesh
namespace Norm { //: namespace IMesh::Norm
	
	class HelloWorld
	{
	public:
		static void Say() {
			std::cout << "This is: " << THIS_FILE << std::endl;
			std::cout << "class IMesh::Norm::HelloWorld" << std::endl;
			std::cout << "Say: Hello World! " << std::endl;
		}
	};

} ///:~ namespace IMesh::Norm
} ///:~ namespace IMesh


int main() 
{
	using namespace IMesh::Norm;
	InitFrom("bunny_simple.obj");
//	cout<<ReadFile("bunny.obj")<<endl;
//	ComputeNorm();
//	AdjustNormDirection();
//	Display(vertices);
//	Display(norm);
	Output();

	getchar();
	return 0;
}
