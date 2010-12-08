#include "StdAfx.h"
#include "IModel.h"


namespace IMesh { namespace UI { namespace Models {

void Model::OnRender()
{
	// do nothing;
}

void ModelCollection::OnRender()
{
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
