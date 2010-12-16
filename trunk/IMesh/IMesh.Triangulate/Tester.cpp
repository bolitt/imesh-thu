#include <iostream>
#include "TriangulationHandler.h"
#include "CloudLoader.h"


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
	testHandler.Initialize(test,4,4,4,0.25,0.1);
	printf("\ninitialOK");

	testHandler.triangulateModel();

	FILE *fp;
	fopen_s(&fp,"testresult.txt","w");

	for(size_t i = 0;i < triangleList.size();i++)
	{
		fprintf(fp,"%ld, %ld, %ld\n",triangleList[i]->idx_i,triangleList[i]->idx_j,triangleList[i]->idx_k);
	}
	fclose(fp);

	system("pause");

	return 0;
}

void generatePoints(vector<norm_point> &test)
{
	for(int i = 1;i<50;i++)
		for(int j = 0;j<60;j++)
		{
			double theta = (double)i*3.14159265358979323846/50;
			double phi = (double)j*3.14159265358979323846/30;

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

			double x = 0.5;
			double y = 0.5;
			double z = 1.0;

			point3D pos(x,y,z);
			vect norm(0.0,0.0,1.0);

			norm_point temp;
			temp.position = pos;
			temp.norm = norm;

			test.push_back(temp);

			x = 0.5;
			y = 0.5;
			z = 0.0;

			point3D pos1(x,y,z);
			vect norm1(0.0,0.0,-1.0);

			norm_point temp1;
			temp1.position = pos1;
			temp1.norm = norm1;

			test.push_back(temp1);

}

//void generatePoints(vector<norm_point> &test)
//{
//	for(int i = 0;i<2;i++)
//		for(int j = 0;j<4;j++)
//		{
//			double theta = (2*(double)i+1)/4*3.14 + (j%2)*0.08;
//			double phi = (double)j/2 * 3.14+i*0.01;
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

//void generatePoints(vector<norm_point> &test)
//{
//	for(int i =0;i<=1;i++)
//		for(int j = 0;j<=1;j++)
//			for(int k = 0;k<=1;k++)
//			{
//				point3D pos((double)i,(double)j,(double)k);
//				vect norm((double)i-0.5,(double)j-0.5,(double)k-0.5);
//				norm_point temp;
//				temp.position=pos;
//				temp.norm=norm;
//
//				test.push_back(temp);
//			}
//}

//void generatePoints(vector<norm_point> &test)
//{
//	using namespace IMesh;
//	using namespace UI;
//
//	CloudLoader *cl = new CloudLoader();
//	cl->Initialize();
//
//	vector<point3D> points = cl->GetPoints();
//	vector<vect> norms = cl->GetNorms();
//
//	long ibound = points.size();
//
//	for(long i = 0;i<ibound;i++)
//	{
//		norm_point temp;
//		temp.position = points[i];
//		temp.norm = norms[i];
//		test.push_back(temp);
//	}
//
//	delete cl;
//}