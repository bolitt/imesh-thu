#include <iostream>
#include "Cloud.h"


static char THIS_FILE[] = __FILE__;



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


	Cloud cloud;
	cloud.InitFromFile("res/bunny.obj");
	cloud.OutToFile();

	Cloud c2;
	c2.InitFromFile("res/bunny_simple.obj");
	c2.OutToFile();
	getchar();
	return 0;
}
