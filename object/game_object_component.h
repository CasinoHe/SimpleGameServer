// Purpose: abstract component base class
// Date: 2018.11.15
// By: CasinoHe

#pragma once

#ifndef SIMPLE_SERVER_OBJECT_GAME_OBJECT_COMPONENT_H
#define SIMPLE_SERVER_OBJECT_GAME_OBJECT_COMPONENT_H

#include "log/log.h"

#include <boost/shared_ptr.hpp>
#include <string>

namespace simple_server {
	class CGameObjectComponent {
		protected:
			boost::shared_ptr<class CGameObject> m_owner;
			std::string m_name;

			CLogManager logger;
		public:
			virtual bool is_serializable() = 0;

			CGameObjectComponent(boost::shared_ptr<class CGameObject> obj_ptr);
			CGameObjectComponent(CGameObjectComponent &comp) = delete;
			virtual ~CGameObjectComponent();
	};
}

#endif
