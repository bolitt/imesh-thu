#include "Cloud.h"
#include <iostream>
#include <stdio.h>
#include <string.h>

namespace IMesh { //: namespace IMesh
namespace Norm { //: namespace IMesh::Norm

	Cloud::Cloud()
	{
		v_num=0;
		k = 15;
		r = 0;
		outname = new char[255];
		norm_finished = false;
	}

	Cloud::~Cloud()
	{
		if ( outname != NULL )
			delete outname;
		m_vertices.clear();
	}

	int Cloud::InitFromFile(  char *strFileName )
	{
		if( ReadFile( strFileName ) != 0)	
			return -1;		// File not open
		ComputeNorm();
		AdjustNormDirection();
		norm_finished = true;
		MoveToZero();
		return 0;
	}

	int Cloud::ReadFile( char *strFileName )
	{
		
		char *str = strFileName;
		int k=0;
		char ch;
	
		//m_FileHandler = fopen_s(strFileName, "r");
		fopen_s(&m_FileHandler, strFileName, "r");
		if (!m_FileHandler) {
			std::cout<<"No such file\n"<<std::endl;;
			return -1;
		}
		while (*str!='.' && *strFileName!='\0') {
			outname[k]=*str;
			k++;
			*str++;
		}
		outname[k]='\0';
		strcat_s(outname,255,"_norm.obj");
	

		while(!feof(m_FileHandler))
		{
			// 获得obj文件中的当前行的第一个字符
			ch = fgetc(m_FileHandler);
			switch(ch)
			{
			case 'v':	// 读入的是'v' (后续的数据是顶点)
				// 读入点的信息
				ReadVertex();
				break;

			default:
			
				break;
			}
		}
	fclose(m_FileHandler);

	v_num= m_vertices.size();

	std::cout<<"V = "<<v_num<<std::endl;
	
	return 0;

	}

	
	void Cloud::ReadVertex()
	{
		Vector3 vNewVertex;

		fscanf_s(m_FileHandler, "%lf %lf %lf", &vNewVertex.x, &vNewVertex.y, &vNewVertex.z);
		m_vertices.push_back(vNewVertex);

		return;
	}

	void Cloud::OutToFile()
	{
		//m_out = fopen_s(outname, "w");
		fopen_s(&m_out, outname, "w");
		if ( norm_finished )
		{
			for ( int i=0; i < v_num; i++) 
			{
				fprintf(m_out, "v %lf %lf %lf norm %lf %lf %lf\n", m_vertices[i].x, m_vertices[i].y, m_vertices[i].z, m_norm[i].x, m_norm[i].y, m_norm[i].z);
			}
		}
		else
		{
			for ( int i=0; i < v_num; i++) 
			{
				fprintf(m_out, "v %lf %lf %lf\n", m_vertices[i].x, m_vertices[i].y, m_vertices[i].z);
			}
		}
		fclose(m_out);
		std::cout<<"Output finished! With Norm "<<norm_finished<<"\n";

		return;
	}

	void Cloud::Output()
	{
		for ( int i=0; i < v_num; i++) 
		{
			printf("v %lf %lf %lf norm %lf %lf %lf\n", m_vertices[i].x, m_vertices[i].y, m_vertices[i].z, m_norm[i].x, m_norm[i].y, m_norm[i].z);
		}
	}
	
} ///:~ namespace IMesh::Norm
} ///:~ namespace IMesh