// Purpose: base class of all game object, abstract class
// Date: 2018.11.15
// By: CasinoHe

#include "object/game_object.h"
#include "object/object_manager.h"

#include <sstream>
#include <string>
#include <memory>

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_serialize.hpp>
#include <boost/uuid/uuid_io.hpp>

namespace simple_server {
	CGameObject::CGameObject(const std::string &name, std::string object_id):
		m_logger(name + "_object") {
		m_component_map.clear();
		m_name = name;

		// generate unique object id
		if (object_id.empty()) {
			boost::uuids::uuid tag = boost::uuids::random_generator()();
			m_object_id = boost::uuids::to_string(tag);
		} else {
			m_object_id = object_id;
		}

		LOG_INFO(m_logger) << "Create game object id [" << m_object_id << "]";
	}

	OArchivePtr CGameObject::get_serialization_data() {
		std::shared_ptr<std::stringstream> ss = std::make_shared<std::stringstream>();
		OArchivePtr os = std::make_shared<OArchive>(*ss);

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

		CObjectManager::OBJECT_MGR_PTR object_manager_ptr = CObjectManager::get_object_manager();
		object_manager_ptr->remove_object(m_object_id);

		LOG_INFO(m_logger) << "Destruct game object id [" << m_object_id << "]";
	}

	bool CGameObject::add_component(const std::string &name, std::shared_ptr<CGameObjectComponent> component) {
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

	std::shared_ptr<CGameObjectComponent> CGameObject::get_component(const std::string &name) {
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

	bool CGameObject::load_components() {
		return true;
	}
}