// Purpose: base class of all game object, abstract class
// Date: 2018.11.15
// By: CasinoHe

#include "object/game_object.h"

#include <sstream>
#include <string>

#include <boost/make_shared.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_serialize.hpp>
#include <boost/uuid/uuid_io.hpp>

namespace simple_server {
	namespace ar = boost::archive;

	CGameObject::CGameObject(const std::string &name) noexcept:
		logger(name + "_object"),
		m_object_id(boost::uuids::random_generator()()) {
		m_component_map.clear();
		m_name = name;
	}

	OArchivePtr CGameObject::get_serialization_data() {
		boost::shared_ptr<std::stringstream> ss = boost::make_shared<std::stringstream>();
		OArchivePtr os = boost::make_shared<OArchive>(*ss);

		(*os) << (*this);
		return os;
	}

	template<typename Archive>
	void CGameObject::serialize(Archive &ar, unsigned const int version) {
		ar & BOOST_SERIALIZATION_NVP(m_object_id);
	}

	CGameObject::~CGameObject() {
		// clear component map
		m_component_map.clear();
	}

	bool CGameObject::add_component(const std::string &name, boost::shared_ptr<CGameObjectComponent> component) {
		if (m_component_map.find(name) != m_component_map.end()) {
			return false;
		} else {
			m_component_map[name] = component;
			return true;
		}
	}

	bool CGameObject::remove_component(const std::string &name) {
		if (m_component_map.find(name) == m_component_map.end()) {
			return false;
		} else {
			m_component_map.erase(name);
		}
		return true;
	}

	boost::shared_ptr<CGameObjectComponent> CGameObject::get_component(const std::string &name) {
		if (m_component_map.find(name) == m_component_map.end()) {
			return nullptr;
		} else {
			return m_component_map[name];
		}
	}
}
