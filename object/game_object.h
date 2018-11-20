// Purpose: abstract base class of all game object
// Date: 2018.11.15
// By: CasinoHe

/*
 * serialization:
 *  Game server always needs to hot reload, this is a key feature.Though we can use
 *   some script languages, simple server will support c++ hot reload for all game 
 *   object.
 *  And sometimes(maybe many times), there is a bug online(For example,a memory leak, 
 *   90% of the memory has been used),we cannot do anything except fix it immediately
 *   or reboot.So, with support to serialization in c++,we can serialize all game 
 *   object and transfer to another new server,get more time to debug and avoid 
 *   pressure from players(PM).
 *  
*/

#pragma once

#ifndef SIMPLE_SERVER_OBJECT_GAME_OBJECT_H
#define SIMPLE_SERVER_OBJECT_GAME_OBJECT_H

#include <boost/dll.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/serialization/serialization.hpp>

#define SIMPLE_SERVER_API extern "C" BOOST_SYMBOL_EXPORT

#define OBJECT_HEAD private:\
	friend boost::serialization::access;

namespace simple_server {
	class CGameObject {

		OBJECT_HEAD;

		private:
			unsigned int object_id;

		private:
			unsigned int generate_id();

		public:
			CGameObject() noexcept;
	};
}

#endif
