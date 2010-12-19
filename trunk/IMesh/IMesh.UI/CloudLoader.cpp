#include "StdAfx.h"
#include "CloudLoader.h"

namespace IMesh { namespace UI {

CloudLoader::CloudLoader(void)
{
}


CloudLoader::~CloudLoader(void)
{
}

void CloudLoader::Initialize()
{
	char* file = "../IMesh.Norm/res/horse.obj";
	m_cloud.InitFromFile(file);
}

std::vector<Num::Vec3f> CloudLoader::GetPoints()
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

std::vector<Num::Vec3f> CloudLoader::GetNorms()
{
	std::vector<Norm::Vector3>& ns = m_cloud.m_norm;
	std::vector<Num::Vec3f> norms;
	for (size_t i = 0; i < ns.size(); ++i)
	{
		Norm::Vector3& v = ns[i];
		Num::Vec3f nn((float)v.x, (float)v.y, (float)v.z);
		norms.push_back(nn);
	}
	return norms;

}


} }
