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
#include <memory>

#include <boost/dll.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>

#define SIMPLE_SERVER_API extern "C" BOOST_SYMBOL_EXPORT

typedef boost::archive::binary_iarchive IArchive;
typedef boost::archive::binary_oarchive OArchive;
typedef std::shared_ptr<IArchive> IArchivePtr;
typedef std::shared_ptr<OArchive> OArchivePtr;

#define SERIALIZE_CLASS_HEAD private:\
		friend boost::serialization::access;\
		template<typename Archive>\
		void serialize(Archive &ar, const unsigned int version);

#define SPLIT_SERIALIZE_CLASS_HEAD private:\
	friend boost::serialization::access;\
	template<typename Archive>\
	void load(Archive &ar, const unsigned int version);\
	template<typename Archive>\
	void save(Archive &ar, const unsigned int version);\
	BOOST_SERIALIZATION_SPLIT_MEMBER()


namespace simple_server {
	class CGameObject: public std::enable_shared_from_this<CGameObject> {

		// class need to be serialized
		SERIALIZE_CLASS_HEAD;

		protected:
			std::string m_object_id;
			std::unordered_map<std::string, std::shared_ptr<CGameObjectComponent> > m_component_map;
			bool add_component(const std::string &name, std::shared_ptr<CGameObjectComponent> component);
			bool remove_component(const std::string &name);
			std::shared_ptr<CGameObjectComponent> get_component(const std::string &name);

			std::string m_name;

		public:
			CGameObject(const std::string &name, std::string object_id);
			virtual ~CGameObject();

			OArchivePtr get_serialization_data();
			inline const std::string &get_object_id() const noexcept {return m_object_id;}

			bool operator==(const CGameObject &object);

			CLogManager m_logger;

			// serialize
			virtual bool is_serializable() = 0;
			// load component
			virtual bool load_components();
	};
}

#endif
