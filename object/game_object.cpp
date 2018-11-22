// Purpose: base class of all game object, abstract class
// Date: 2018.11.15
// By: CasinoHe

#include "object/game_object.h"

#include <sstream>
#include <string>

#include <boost/make_shared.hpp>

namespace simple_server {
	namespace ar = boost::archive;

	CGameObject::CGameObject() noexcept {
		m_object_id = 0;
		m_component_map.clear();

		generate_id();
	}

	unsigned int CGameObject::generate_id() {
		m_object_id = 1;
		return m_object_id;
	}

	OArchivePtr CGameObject::get_serialization_data() {
		boost::shared_ptr<std::stringstream> ss = boost::make_shared<std::stringstream>();
		OArchivePtr os = boost::make_shared<OArchive>(*ss);

		(*os) << (*this);
		return nullptr;
	}

	template<typename Archive>
	void CGameObject::serialize(Archive &ar, unsigned const int version) {
		ar & m_object_id;
	}

	CGameObject::~CGameObject() {
		// clear component map
		m_component_map.clear();
	}
}
