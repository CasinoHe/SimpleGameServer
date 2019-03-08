// Purpose: Object manager method
// Date: 2019.02.18
// By: CasinoHe

#pragma once

#ifndef SIMPLE_SERVER_OBJECT_OBJECT_HELPER
#define SIMPLE_SERVER_OBJECT_OBJECT_HELPER

#include "log/log.h"
#include "object/game_object.h"
#include "object/object_manager.h"

#include <string>
#include <memory>


namespace simple_server {
    class CObjectHelper {
        public:
            template<typename T>
            static std::shared_ptr<T> create_object(const std::string &name, std::string object_id = std::string());

            CObjectHelper(): m_logger("ObjectHelper") {}

            CLogManager m_logger;
    };

    template<typename T>
    std::shared_ptr<T> CObjectHelper::create_object(const std::string &name, std::string object_id) {
        std::shared_ptr<T> object_ptr = std::make_shared<T>(name, object_id);
        if (!object_ptr) {
            return nullptr;
        }

        // add components
        object_ptr->load_components();

        // get object manager instance pointer
		CObjectManager::OBJECT_MGR_PTR object_manager_ptr = CObjectManager::get_object_manager();
        // add object to object manager
		if (!object_manager_ptr->add_object(object_ptr)) {
			std::string error("Cannot add object :");
			error += object_ptr->get_object_id();

			LOG_ERROR(object_ptr->m_logger) << error;
			throw std::runtime_error(error);
		}

        return object_ptr;
    }
}

#endif