// Purpose: Prepare for connection
// Date: 2019.02.16
// By: CasinoHe

#pragma once

#ifndef SIMPLE_SERVER_OBJECT_CONNECTION_OBJECT_H
#define SIMPLE_SERVER_OBJECT_CONNECTION_OBJECT_H

#include "object/game_object.h"

#include <boost/asio.hpp>
#include <boost/chrono.hpp>

#include <string>

namespace simple_server {
    class CConnectionObject: public CGameObject {

        // Connection object should not to be serializable
        // SERIALIZE_CLASS_HEAD;

        public:
            CConnectionObject() = delete;
            CConnectionObject(const std::string &name = std::string("Connection"), std::string object_id = std::string());
            virtual ~CConnectionObject();

            inline virtual bool is_serializable() {return false;}

        private:
            boost::chrono::time_point<boost::chrono::steady_clock> m_connect_time;
    };
}

#endif