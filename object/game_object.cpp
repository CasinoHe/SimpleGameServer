// Purpose: base class of all game object, abstract class
// Date: 2018.11.15
// By: CasinoHe

#include "object/game_object.h"
#include "object/object_manager.h"

#include <sstream>
#include <string>

#include <boost/make_shared.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_serialize.hpp>
#include <boost/uuid/uuid_io.hpp>

namespace simple_server {
	CGameObject::CGameObject(const std::string &name, std::string &object_id):
		logger(name + "_object") {
		m_component_map.clear();
		m_name = name;

		// generate unique object id
		if (object_id.empty()) {
			boost::uuids::uuid tag = boost::uuids::random_generator()();
			m_object_id = boost::uuids::to_string(tag);
		} else {
			m_object_id = object_id;
		}

		CObjectManager object_manager = CObjectManager::get_object_manager();
		if (!object_manager.add_object(shared_from_this())) {
			std::string error("Cannot add object :");
			error += m_object_id;

			LOG_ERROR(logger) << error;
			throw std::runtime_error(error);
		}
	}

	OArchivePtr CGameObject::get_serialization_data() {
		boost::shared_ptr<std::stringstream> ss = boost::make_shared<std::stringstream>();
		OArchivePtr os = boost::make_shared<OArchive>(*ss);

		(*os) << (*this);
		return os;
	}

	template<typename Archive>
	void CGameObject::serialize(Archive &ar, unsigned const int version) {
		ar & m_name;
		ar & m_object_id;
	}

	CGameObject::~CGameObject() {
		// clear component map
		m_component_map.clear();

		CObjectManager &object_manager = CObjectManager::get_object_manager();
		object_manager.remove_object(m_object_id);
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

	bool CGameObject::operator==(const CGameObject &object) {
		if (object.get_object_id() == m_object_id) {
			return true;
		} else {
			return false;
		}
	}
}
