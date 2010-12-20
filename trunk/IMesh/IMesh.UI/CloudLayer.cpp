#include "StdAfx.h"
#include "CloudLayer.h"

namespace IMesh { namespace UI { namespace Models {

CloudLayer::CloudLayer(void)
{
	m_pAdjuster = NULL;

}


CloudLayer::~CloudLayer(void)
{
	ClearLayer();
}


void CloudLayer::ClearLayer()
{
	this->m_children.clear();

	for (size_t i = 0; i < m_vertiesHolder.size(); ++i)
	{
		delete m_vertiesHolder[i];
	}
	m_vertiesHolder.clear();

	for (size_t i = 0; i < m_edgesHolder.size(); ++i)
	{
		delete m_edgesHolder[i];
	}
	m_edgesHolder.clear();
}

void CloudLayer::SetLayer(CloudInit& cloud)
{
	ClearLayer();
	{
		using namespace IMesh::UI;
		using namespace IMesh::Norm;

		std::vector<Num::Vec3f>& points = cloud.GetPoints();
		std::vector<Num::Vec3f>& norms = cloud.GetNorms();
		ASSERT(points.size() == norms.size());

		for (size_t i = 0; i < points.size(); i++) {
			Num::Vec3f& point = points[i];
			if (m_pAdjuster != NULL) {
				point = m_pAdjuster->Adjust(point);
			}
			Num::Vec3f& norm = norms[i];

			Vertex* v0 = new Vertex();
			v0->m_id = i;
			v0->m_pos = point;
			m_vertiesHolder.push_back(v0);

			Vertex* v1 = new Vertex();
			// v1->m_id = 2 * i + 1; //helper vertex doesn't has id
			v1->m_pos = point + norm;

			Edge* e = new Edge();
			e->m_id = i;
			e->_pV0 = v0;
			e->_pV1 = v1;
			m_edgesHolder.push_back(e);
		}
		for (size_t i = 0; i < m_vertiesHolder.size(); i++)
		{
			this->m_children.push_back(m_vertiesHolder[i]);
		}
		for (size_t i = 0; i < m_edgesHolder.size(); i++)
		{
			this->m_children.push_back(m_edgesHolder[i]);
		}
	}
}

void CloudLayer::OnRender()
{
	if (!m_IsVisible) return;

	glPushMatrix();

	parent_type::OnRender();

	glPopMatrix();

	_DEBUG_ONRENDER_CHECK_ERROR_();
}

} } }