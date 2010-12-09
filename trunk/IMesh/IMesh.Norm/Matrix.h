//Matrix.h

#ifndef _MATRIX_H
#define _MATRIX_H

#include<vector>
#include<list>
#include<iostream>
#include<math.h>

using namespace std;


class Vector3{
public:
	double x,y,z;
	vector<int> tree_neighbour;
	bool adjusted;
	//double nx,ny,nz;
	Vector3(){ x = y = z = 0; adjusted = false;}
	Vector3(double a, double b, double c){ x=a, y=b, z=c; adjusted = false;}
	
	inline double get(int i)
	{
		switch(i){
		case 0:
			return x;
		case 1:
			return y;
		case 2:
			return z;
		default:
			return 0;
		}
	}
	void neg(){
		x = -x;
		y = -y;
		z = -z;
	}
	double innerProduct(Vector3& v)
	{
		return x*v.x+y*v.y+z*v.z;
	}
};

class Edge{
public:
	int u,v;
	double length;
	Edge(int,int);
};


class Matrix{
public:
	double m_mat[3][3];
	Matrix(){ };
	Matrix( vector<int> &v );
	void Show();
	Vector3 Solve();
};


#endif // _MATRIX_H