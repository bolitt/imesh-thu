#pragma once

#ifndef _CLOUD_H
#define _CLOUD_H


#include"Vec.h"




namespace IMesh { //: namespace IMesh
namespace Norm { //: namespace IMesh::Norm
	
	class Cloud
	{
	public:
		static std::vector<Vector3>* p_vertices;	//vertices
		static Vector3 origin;
		std::vector<Vector3> m_vertices;	//vertices
		std::vector<Vector3> m_norm;			// norms
		std::vector<Edge> m_edges;				//edges of nearest neighbours
		int v_num;		//number of vertices
		int k;				//compute for k nearest neighbours;
		double r;				//radious

		FILE *m_FileHandler;	//source obj file
		FILE *m_out;			//target obj file
		char *outname;			//output file name
		bool norm_finished;		//whether norm has been computed

		/***
		Following functions are in Cloud_Norm.cpp
		***/
		static bool DisCmp( int u, int v);		//compare distance
		static bool DisCmp2( Vector3 &u, Vector3 &v);
		Vector3 ComputeOneNorm(int );
		int ComputeNorm();
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