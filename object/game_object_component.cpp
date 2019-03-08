// Purpose: abstract component base class implementation
// Date: 2018.11.15
// By: CasinoHe

#include "object/game_object.h"
#include "object/game_object_component.h"

namespace simple_server {
	CGameObjectComponent::CGameObjectComponent(std::shared_ptr<CGameObject> obj_ptr, const std::string &name):
		logger(name + "_component") {
		m_owner = obj_ptr;
		m_name = name;
	}

	CGameObjectComponent::~CGameObjectComponent() {
	}
}
