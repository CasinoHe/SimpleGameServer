// Purpose: abstract component base class
// Date: 2018.11.15
// By: CasinoHe

#pragma once

#ifndef SIMPLE_SERVER_OBJECT_GAME_OBJECT_COMPONENT_H
#define SIMPLE_SERVER_OBJECT_GAME_OBJECT_COMPONENT_H

#include "log/log.h"

#include <string>

#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>

namespace simple_server {
	class CGameObjectComponent: public boost::noncopyable {
		protected:
			boost::shared_ptr<class CGameObject> m_owner;
			std::string m_name;

			CLogManager logger;
		public:
			virtual bool is_serializable() = 0;

			CGameObjectComponent(boost::shared_ptr<class CGameObject> obj_ptr, const std::string &name);
			CGameObjectComponent(CGameObjectComponent &comp) = delete;
			virtual ~CGameObjectComponent();

			inline const std::string &get_component_name() noexcept {return m_name;}
	};
}

#endif
