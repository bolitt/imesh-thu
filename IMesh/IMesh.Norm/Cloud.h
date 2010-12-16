#pragma once

#ifndef _CLOUD_H
#define _CLOUD_H


#include"Vec.h"




namespace IMesh { //: namespace IMesh
namespace Norm { //: namespace IMesh::Norm
	
	class Cloud
	{
	public:
		std::vector<Vector3> m_vertices;	//vertices
		std::vector<Vector3> m_norm;			// norms
		std::vector<Edge> m_edges;				//edges of nearest neighbours
		int v_num;		//number of vertices
		int k;				//compute for k nearest neighbours;
		double r;				//radious
		int lowest;			//lowest point

		FILE *m_FileHandler;	//source obj file
		FILE *m_out;			//target obj file
		char *outname;			//output file name
		bool norm_finished;		//whether norm has been computed

		/***
		Following functions are in Cloud_Norm.cpp
		***/

		Vector3 ComputeOneNorm(int );
		int ComputeNorm();
		int MoveToZero();
		int AdjustNormDirection();

		/***
		Following functions are in Cloud.cpp
		***/
		void ReadVertex();
		int ReadFile( char *strFileName );

//		void Display( std::vector<Vector3> &v);

	public:
		Cloud();
		~Cloud();
		void OutToFile();
		void Output();
		int InitFromFile( char *strFileName );


	};

} ///:~ namespace IMesh::Norm
} ///:~ namespace IMesh

#endif	//~_CLOUD_H