// ModGenetator.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<string>
#include<fstream>
#include<math.h>

void makeCubeOffset();

using namespace std;



void makeCubeOffset(FILE *m_out, int n, double dx = 0, double dy = 0, double dz = 0)
{
	fprintf(m_out, "v %lf %lf %lf\n", dx+1.0, dy+1.0, dz+1.0);
	fprintf(m_out, "v %lf %lf %lf\n", dx+0.0, dy+1.0, dz+1.0);
	fprintf(m_out, "v %lf %lf %lf\n", dx+1.0, dy+0.0, dz+1.0);
	fprintf(m_out, "v %lf %lf %lf\n", dx+0.0, dy+0.0, dz+1.0);
	fprintf(m_out, "v %lf %lf %lf\n", dx+1.0, dy+1.0, dz+0);
	fprintf(m_out, "v %lf %lf %lf\n", dx+0.0, dy+1.0, dz+0);
	fprintf(m_out, "v %lf %lf %lf\n", dx+1.0, dy+0.0, dz+0);
	fprintf(m_out, "v %lf %lf %lf\n", dx+0.0, dy+0.0, dz+0);
	for( int i = 1; i < n ; i++)
	{
		for( int j = 1 ; j < n ; j++ )
		{
			fprintf(m_out, "v %lf %lf %lf\n", dx+1.0, dy+1.0/n*i, dz+1.0/n*j);
			fprintf(m_out, "v %lf %lf %lf\n", dx+0.0, dy+1.0/n*i, dz+1.0/n*j);
			fprintf(m_out, "v %lf %lf %lf\n", dx+1.0/n*i, dy+1.0, dz+1.0/n*j);
			fprintf(m_out, "v %lf %lf %lf\n", dx+1.0/n*i, dy+0.0, dz+1.0/n*j);
			fprintf(m_out, "v %lf %lf %lf\n", dx+1.0/n*i, dy+1.0/n*j, dz+1.0);
			fprintf(m_out, "v %lf %lf %lf\n", dx+1.0/n*i, dy+1.0/n*j, dz+0.0);
		}
		fprintf(m_out, "v %lf %lf %lf\n", dx+1.0, dy+1.0, dz+1.0/n*i);
		fprintf(m_out, "v %lf %lf %lf\n", dx+0.0, dy+1.0, dz+1.0/n*i);
		fprintf(m_out, "v %lf %lf %lf\n", dx+1.0, dy+0.0, dz+1.0/n*i);
		fprintf(m_out, "v %lf %lf %lf\n", dx+0.0, dy+0.0, dz+1.0/n*i);
		fprintf(m_out, "v %lf %lf %lf\n", dx+1.0/n*i, dy+1.0, dz+1.0);
		fprintf(m_out, "v %lf %lf %lf\n", dx+1.0/n*i, dy+0.0, dz+1.0);
		fprintf(m_out, "v %lf %lf %lf\n", dx+1.0/n*i, dy+1.0, dz+0.0);
		fprintf(m_out, "v %lf %lf %lf\n", dx+1.0/n*i, dy+0.0, dz+0.0);
		fprintf(m_out, "v %lf %lf %lf\n", dx+1.0, dy+1.0/n*i, dz+1.0);
		fprintf(m_out, "v %lf %lf %lf\n", dx+0.0, dy+1.0/n*i, dz+1.0);
		fprintf(m_out, "v %lf %lf %lf\n", dx+1.0, dy+1.0/n*i, dz+0.0);
		fprintf(m_out, "v %lf %lf %lf\n", dx+0.0, dy+1.0/n*i, dz+0.0);
	}
}


void makeCube(int n)
{
	char *fn = "cube_triple.obj";
	FILE *m_out;
	fopen_s(&m_out, fn, "w");
	
	makeCubeOffset(m_out, n);
	makeCubeOffset(m_out, n, -0.5, -0.5, 0);
	makeCubeOffset(m_out, n, 0.5, 0.5, 0);
	

	fclose(m_out);
}

void makeBall(int n)
{
	char *fn = "ball.obj";
	FILE *m_out;
	fopen_s(&m_out, fn, "w");
	double pie = 3.1415926535;
	double d = pie*0.5/n;
	
	fprintf(m_out, "v %lf %lf %lf\n", 0.0,0.0,1.0);
	fprintf(m_out, "v %lf %lf %lf\n", 0.0,0.0,-1.0 );
	for( int i = 0; i < n ; i++)
	{
		double c = cos(d*i);
		double s = sin(d*i);
		fprintf(m_out, "v %lf %lf %lf\n", c, s, 0);
		fprintf(m_out, "v %lf %lf %lf\n", s, -c, 0 );
		fprintf(m_out, "v %lf %lf %lf\n", -c, -s, 0);
		fprintf(m_out, "v %lf %lf %lf\n", -s, c, 0 );
		for( int j = 1 ; j < n ; j++ )
		{
			
				double z = sin(d*j);
				double r = sqrt(1.0-z*z);
				double x = r*c;
				double y = r*s;
				fprintf(m_out, "v %lf %lf %lf\n", x, y, z);
				fprintf(m_out, "v %lf %lf %lf\n", y, -x, z );
				fprintf(m_out, "v %lf %lf %lf\n", -x, -y, z);
				fprintf(m_out, "v %lf %lf %lf\n", -y, x, z );
				fprintf(m_out, "v %lf %lf %lf\n", x, y, -z);
				fprintf(m_out, "v %lf %lf %lf\n", y, -x, -z );
				fprintf(m_out, "v %lf %lf %lf\n", -x, -y, -z);
				fprintf(m_out, "v %lf %lf %lf\n", -y, x, -z );
			
		}	
	}
	fclose(m_out);
}

void makeCylinder(int n)
{
	char *fn = "Cylinder.obj";
	FILE *m_out;
	fopen_s(&m_out, fn, "w");
	double pie = 3.1415926535;
	double d = pie*0.5/n;
	
	fprintf(m_out, "v %lf %lf %lf\n", 0.0,0.0,1.0);
	fprintf(m_out, "v %lf %lf %lf\n", 0.0,0.0,-1.0 );
	for( int i = 0; i < n ; i++)
	{
		double c = cos(d*i);
		double s = sin(d*i);
		fprintf(m_out, "v %lf %lf %lf\n", c, s, 0.0);
		fprintf(m_out, "v %lf %lf %lf\n", s, -c, 0.0 );
		fprintf(m_out, "v %lf %lf %lf\n", -c, -s, 0.0);
		fprintf(m_out, "v %lf %lf %lf\n", -s, c, 0.0 );

		fprintf(m_out, "v %lf %lf %lf\n", c, s, 1.0);
		fprintf(m_out, "v %lf %lf %lf\n", s, -c, 1.0 );
		fprintf(m_out, "v %lf %lf %lf\n", -c, -s, 1.0);
		fprintf(m_out, "v %lf %lf %lf\n", -s, c, 1.0 );
		fprintf(m_out, "v %lf %lf %lf\n", c, s, -1.0);
		fprintf(m_out, "v %lf %lf %lf\n", s, -c, -1.0 );
		fprintf(m_out, "v %lf %lf %lf\n", -c, -s, -1.0);
		fprintf(m_out, "v %lf %lf %lf\n", -s, c, -1.0 );

		for( double j = 1 ; j < n ; j++ )
		{
			
				double z = sin(d*j);
				double r = sqrt(1.0-z*z);
				double x = r*c;
				double y = r*s;
				fprintf(m_out, "v %lf %lf %lf\n", x, y, 1.0);
				fprintf(m_out, "v %lf %lf %lf\n", y, -x, 1.0 );
				fprintf(m_out, "v %lf %lf %lf\n", -x, -y, 1.0);
				fprintf(m_out, "v %lf %lf %lf\n", -y, x, 1.0 );
				fprintf(m_out, "v %lf %lf %lf\n", x, y, -1.0);
				fprintf(m_out, "v %lf %lf %lf\n", y, -x, -1.0 );
				fprintf(m_out, "v %lf %lf %lf\n", -x, -y, -1.0);
				fprintf(m_out, "v %lf %lf %lf\n", -y, x, -1.0 );
				
				fprintf(m_out, "v %lf %lf %lf\n", c, s, j/n);
				fprintf(m_out, "v %lf %lf %lf\n", s, -c,  j/n);
				fprintf(m_out, "v %lf %lf %lf\n", -c, -s, j/n);
				fprintf(m_out, "v %lf %lf %lf\n", -s, c, j/n );
				fprintf(m_out, "v %lf %lf %lf\n", c, s, -j/n);
				fprintf(m_out, "v %lf %lf %lf\n", s, -c, -j/n );
				fprintf(m_out, "v %lf %lf %lf\n", -c, -s, -j/n);
				fprintf(m_out, "v %lf %lf %lf\n", -s, c, -j/n );
			
		}	
	}
	fclose(m_out);
}

int _tmain(int argc, _TCHAR* argv[])
{
	makeCylinder(8);
	//makeCube(6);
	return 0;
}

