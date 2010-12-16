#pragma once

#ifndef _VEC_H
#define _VEC_H

#include<vector>


namespace IMesh { //: namespace IMesh
namespace Norm { //: namespace IMesh::Norm

class Vector3{
public:
	double x,y,z;
	std::vector<int> tree_neighbour;
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

	void operator -=( Vector3&);
};

	
double SquareOfDistance( Vector3 &u, Vector3 &v);


class Edge{
public:
	int u,v;
	double weight;
	Edge(int i,int j, double w);
};

bool cmplength(Edge e, Edge f);
	
} ///:~ namespace IMesh::Norm
} ///:~ namespace IMesh

#endif	//~ _VEC_H