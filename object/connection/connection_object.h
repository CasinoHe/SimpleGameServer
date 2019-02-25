// Purpose: Prepare for connection
// Date: 2019.02.16
// By: CasinoHe

#pragma once

#ifndef SIMPLE_SERVER_OBJECT_CONNECTION_OBJECT_H
#define SIMPLE_SERVER_OBJECT_CONNECTION_OBJECT_H

#include "object/game_object.h"

#include <boost/asio.hpp>
#include <boost/chrono.hpp>
#include <boost/shared_ptr.hpp>

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

            bool set_tcp_connection(boost::asio::ip::tcp::socket socket);
            bool set_udp_connection(boost::asio::ip::udp::socket &socket);

            virtual bool load_components();
        private:
            boost::chrono::time_point<boost::chrono::steady_clock> m_connect_time;

            boost::shared_ptr<boost::asio::ip::tcp::socket> m_tcp_socket_ptr;
            boost::shared_ptr<boost::asio::ip::udp::socket> m_udp_socket_ptr;
    };
}

#endif