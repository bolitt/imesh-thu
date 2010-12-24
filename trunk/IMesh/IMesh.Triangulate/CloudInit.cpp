#include "CloudInit.h"


namespace IMesh { namespace UI {

CloudInit::CloudInit(void)
{
}


CloudInit::~CloudInit(void)
{
}

void CloudInit::RunTriangulate()
{
	vector<norm_point> nps;
	for( int i = 0 ; i < m_cloud.v_num ; i++ )
	{
		norm_point temp;
		temp.position = point3D(m_cloud.m_vertices[i].x,m_cloud.m_vertices[i].y,m_cloud.m_vertices[i].z);
		temp.norm = vect(m_cloud.m_norm[i].x,m_cloud.m_norm[i].y,m_cloud.m_norm[i].z);
		nps.push_back(temp);
	}
	m_triangleHandler.Initialize(nps, 
							m_cloud.grid_x,m_cloud.grid_y,m_cloud.grid_z,
							m_cloud.grid_width, 
							m_cloud.density);
	m_triangleHandler.triangulateModel();
}

void CloudInit::Initialize()
{
	char* file = "../IMesh.Norm/res/frog_s2.obj";
	Initialize(file);
}

void CloudInit::Initialize(char* file)
{
	m_cloud.InitFromFile(file);
}



std::vector<Num::Vec3f> CloudInit::GetPoints()
{
	std::vector<Norm::Vector3>& vs = m_cloud.m_vertices;
	std::vector<Num::Vec3f> points;
	for (size_t i = 0; i < vs.size(); ++i)
	{
		Norm::Vector3& v = vs[i];
		Num::Vec3f n((float)v.x, (float)v.y, (float)v.z);
		points.push_back(n);
	}
	return points;
}

std::vector<Num::Vec3f> CloudInit::GetNorms()
{
	std::vector<Norm::Vector3>& ns = m_cloud.m_norm;
	std::vector<Num::Vec3f> norms;
	for (size_t i = 0; i < ns.size(); ++i)
	{
		Norm::Vector3& v = ns[i];
		Num::Vec3f nn(v.x, v.y, v.z);
		norms.push_back(nn);
	}
	return norms;

}

Num::Vec3f CloudInit::GetLowestDim()
{
	Norm::Vector3& v = m_cloud.lowestDim;
	return Num::Vec3f(v.x, v.y, v.z);
}

Num::Vec3f CloudInit::GetHighestDim()
{
	Norm::Vector3& v = m_cloud.highestDim;
	return Num::Vec3f(v.x, v.y, v.z);
}

Num::Vec3f CloudInit::GetMiddleDim()
{
	Norm::Vector3& v = m_cloud.middleDim;
	return Num::Vec3f(v.x, v.y, v.z);
}

//
//std::vector<point3D> CloudInit::GetPoints()
//{
//	std::vector<Norm::Vector3>& vs = m_cloud.m_vertices;
//	std::vector<point3D> points;
//	for (size_t i = 0; i < vs.size(); ++i)
//	{
//		Norm::Vector3& v = vs[i];
//		point3D n(v.x, v.y, v.z);
//		points.push_back(n);
//	}
//	return points;
//}
//
//std::vector<vect> CloudInit::GetNorms()
//{
//	std::vector<Norm::Vector3>& ns = m_cloud.m_norm;
//	std::vector<vect> norms;
//	for (size_t i = 0; i < ns.size(); ++i)
//	{
//		Norm::Vector3& v = ns[i];
//		vect nn(v.x, v.y, v.z);
//		norms.push_back(nn);
//	}
//	return norms;
//
//}

} }
