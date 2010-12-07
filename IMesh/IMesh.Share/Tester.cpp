#include <iostream>
#include "../IMesh.UI/vec.h"
#include "../IMesh.UI/Tester.h"

using namespace std;

int main() 
{	
	{   
		using namespace IMesh::Num::Test;

		cout << "=== BEGIN: Test IMesh.Share ===" << endl;
		Tester::Run();
		cout << "=== END: Test IMesh.Share PASSED! ===" << endl;
	}	
	getchar();
	return 0;
}
