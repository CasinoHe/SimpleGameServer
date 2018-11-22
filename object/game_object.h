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

#include "log/log.h"
#include "object/game_object_component.h"

#include <vector>
#include <string>
#include <unordered_map>

#include <boost/dll.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/archive/polymorphic_binary_iarchive.hpp>
#include <boost/archive/polymorphic_binary_oarchive.hpp>

#define SIMPLE_SERVER_API extern "C" BOOST_SYMBOL_EXPORT

typedef boost::archive::polymorphic_binary_iarchive IArchive;
typedef boost::archive::polymorphic_binary_oarchive OArchive;
typedef boost::shared_ptr<IArchive> IArchivePtr;
typedef boost::shared_ptr<OArchive> OArchivePtr;

#define SERIALIZE_CLASS_HEAD private:\
		friend boost::serialization::access;\
		template<typename Archive>\
		void serialize(Archive &ar, const unsigned int version);

#define SPLIT_ SERIALIZE_CLASS_HEAD private:\
	friend boost::serialization::access;\
	template<typename Archive>\
	void load(Archive &ar, const unsigned int version);\
	template<typename Archive>\
	void save(Archive &ar, const unsigned int version);\
	BOOST_SERIALIZATION_SPLIT_MEMBER()


namespace simple_server {
	class CGameObject {

		// class need to be serialized
		SERIALIZE_CLASS_HEAD;

		protected:
			unsigned int m_object_id;
			std::unordered_map<std::string, boost::shared_ptr<CGameObjectComponent> > m_component_map;
			bool add_component(const std::string &name, boost::shared_ptr<CGameObjectComponent> component);
			bool remove_component(const std::string &name);
			boost::shared_ptr<CGameObjectComponent> get_component(const std::string &name);

			std::string m_name;
			CLogManager logger;
		private:
			unsigned int generate_id();

		public:
			CGameObject(const std::string &name) noexcept;
			virtual ~CGameObject();

			OArchivePtr get_serialization_data();
			inline unsigned int get_object_id() noexcept {return m_object_id;}

			// serialize
			virtual bool is_serializable() = 0;
	};
}

#endif
