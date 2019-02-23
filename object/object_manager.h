// Purpose: global manager for game object.Find object by object id from the manager
// Date: 2018.11.29
// By: CasinoHe

#pragma once

#ifndef SIMPLE_SERVER_OBJECT_OBJECT_MANAGER
#define SIMPLE_SERVER_OBJECT_OBJECT_MANAGER

#include "object/game_object.h"

#include <string>
#include <unordered_map>

#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>

namespace simple_server {
	class CObjectManager: public boost::noncopyable {
		public:
			typedef boost::shared_ptr<CGameObject> GAME_OBJECT_PTR;
			typedef boost::shared_ptr<CObjectManager> OBJECT_MGR_PTR;

			static OBJECT_MGR_PTR get_object_manager();
		private:
			std::unordered_map<std::string, GAME_OBJECT_PTR> m_all_game_objects;

		public:
			GAME_OBJECT_PTR find_object(const std::string &object_id);
			bool add_object(GAME_OBJECT_PTR object);
			bool remove_object(GAME_OBJECT_PTR object);
			bool remove_object(const std::string &object_id);
	};
}

#endif
