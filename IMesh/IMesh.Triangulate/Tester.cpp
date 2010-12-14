#include <iostream>
#include "TriangulationHandler.h"

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

void generatePoints(vector<norm_point> &test);

int main() 
{
	using namespace IMesh::Triangulate;
	
	//HelloWorld::Say();
	//getchar();
	vector<norm_point> test;
	generatePoints(test);

	printf("\npreparationOK");
	TriangulationHandler testHandler;
	testHandler.Initialize(test,1,1,1,2.0,1.0);
	printf("\ninitialOK");

	testHandler.triangulateModel();

	FILE *fp;
	fp = fopen("testresult.txt","w");

	for(int i = 0;i < triangleList.size();i++)
	{
		fprintf(fp,"%ld, %ld, %ld\n",triangleList[i]->idx_i,triangleList[i]->idx_j,triangleList[i]->idx_k);
	}
	fclose(fp);


	getchar();
	return 0;
}

//void generatePoints(vector<norm_point> &test)
//{
//	for(int i = 0;i<31;i++)
//		for(int j = 0;j<62;j++)
//		{
//			double theta = (double)i/10.0f;
//			double phi = (double)j/10.0f;
//
//			double x = 0.5+0.5*sin(theta)*cos(phi);
//			double y = 0.5+0.5*sin(theta)*sin(phi);
//			double z = 0.5+0.5*cos(theta);
//
//			point3D pos(x,y,z);
//			vect norm(sin(theta)*cos(phi),sin(theta)*sin(phi),cos(theta));
//
//			norm_point temp;
//			temp.position = pos;
//			temp.norm = norm;
//
//			test.push_back(temp);
//		}
//}

void generatePoints(vector<norm_point> &test)
{
	for(int i = 0;i<2;i++)
		for(int j = 0;j<4;j++)
		{
			double theta = (2*(double)i+1)/4*3.14 + (j%2)*0.08;
			double phi = (double)j/2 * 3.14+i*0.01;

			double x = 0.5+0.5*sin(theta)*cos(phi);
			double y = 0.5+0.5*sin(theta)*sin(phi);
			double z = 0.5+0.5*cos(theta);

			point3D pos(x,y,z);
			vect norm(sin(theta)*cos(phi),sin(theta)*sin(phi),cos(theta));

			norm_point temp;
			temp.position = pos;
			temp.norm = norm;

			test.push_back(temp);
		}
}
