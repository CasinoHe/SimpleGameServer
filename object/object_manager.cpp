// Purpose: global manager for game object.Find object by object id from the manager
// Date: 2018.11.29
// By: CasinoHe

#include "object/object_manager.h"

#include <string>

namespace simple_server {
	CObjectManager& CObjectManager::get_object_manager() {
		static CObjectManager object_manager;
		return object_manager;
	}

	CObjectManager::GAME_OBJECT_PTR CObjectManager::find_object(const std::string &object_id) {
		if (m_all_game_objects.find(object_id) != m_all_game_objects.end()) {
			return m_all_game_objects[object_id];
		}
		return nullptr;
	}

	bool CObjectManager::add_object(CObjectManager::GAME_OBJECT_PTR object) {
		const std::string &object_id(object->get_object_id());
		if (find_object(object_id)) {
			return false;
		}

		m_all_game_objects[object_id] = object;
		return true;
	}

	bool CObjectManager::remove_object(CObjectManager::GAME_OBJECT_PTR object) {
		const std::string &object_id(object->get_object_id());
		return remove_object(object_id);
	}

	bool CObjectManager::remove_object(const std::string &object_id) {
		if (!find_object(object_id)) {
			return false;
		} else {
			m_all_game_objects.erase(object_id);
			return true;
		}
	}
}
