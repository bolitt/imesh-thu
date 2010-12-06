#include <iostream>

static char THIS_FILE[] = __FILE__;

namespace IMesh { //: namespace IMesh
namespace Triangulate { //: namespace IMesh::Triangulate
	
	class HelloWorld
	{
	public:
		static void Say() {
			std::cout << "This is: " << THIS_FILE << std::endl;
			std::cout << "class IMesh::Triangulate::HelloWorld" << std::endl;
			std::cout << "Say: Hello World! " << std::endl;
		}
	};

} ///:~ namespace IMesh::Triangulate
} ///:~ namespace IMesh


int main() 
{
	using namespace IMesh::Triangulate;
	
	HelloWorld::Say();
	getchar();

	return 0;
}
