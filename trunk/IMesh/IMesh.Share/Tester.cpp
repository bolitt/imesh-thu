#include <iostream>
#include "vec.h"
#include "num_test.h"
#include "interface_test.h"

using namespace std;

int main() 
{	
	{
		using namespace IMesh::Num::Test;

		cout << "=== BEGIN: Test Num ===" << endl;
		Tester::Run();
		cout << "=== END: Test Num PASSED! ===" << endl;
	}
	{
		using namespace IMesh::Interface::Test;

		cout << "=== BEGIN: Test Interface ===" << endl;
		Tester::Run();
		cout << "=== END: Test Interface PASSED! ===" << endl;
	}
	getchar();
	return 0;
}
