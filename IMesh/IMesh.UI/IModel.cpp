#include "StdAfx.h"
#include "IModel.h"


namespace IMesh { namespace UI { namespace Models {

Model::Model() : m_IsVisible(true)
{

}


Model::~Model()
{

}

void Model::OnRender()
{
	// do nothing!
}

void Model::OnSetup()
{
	// customized setup, should called before OnRender
}

void Model::OnDestroy()
{
	// customized destroy, should called before destructor
}


void ModelCollection::OnRender()
{
	if (!m_IsVisible) return;
	
	parent_type::OnRender();

	children_type& children = this->m_children;
	for (size_t i = 0; i < children.size(); ++i) {
		base_type* pModel = children[i];
		if (pModel != NULL) {
			pModel->OnRender();
		}
	}
	
}

} } } ///:~ IMesh::UI::Models
