// Purpose: Prepare for connection
// Date: 2019.02.16
// By: CasinoHe

#include "log/log.h"
#include "object/connection/connection_object.h"
#include "object/component/schedule_component.h"


namespace simple_server {
    CConnectionObject::CConnectionObject(const std::string &name, std::string object_id):
     CGameObject(name, object_id),
     m_tcp_socket_ptr(nullptr),
     m_udp_socket_ptr(nullptr) {
         m_connect_time = std::chrono::steady_clock::now();
    }

    CConnectionObject::~CConnectionObject() {
        if (m_tcp_socket_ptr) {
            if (m_tcp_socket_ptr->is_open()) {
                m_tcp_socket_ptr->close();
            }

            m_tcp_socket_ptr.reset();
        }

        if (m_udp_socket_ptr) {
            if (m_udp_socket_ptr->is_open()) {
            m_udp_socket_ptr->close();
            }

            m_udp_socket_ptr.reset();
        }

        LOG_DEBUG(m_logger) << "Destruct Connection Object: " << m_object_id;
    }

    bool CConnectionObject::load_components() {
        // add schedule component
        std::shared_ptr<CScheduleComponent> schedule_comp = std::make_shared<CScheduleComponent>(shared_from_this());
        add_component(schedule_comp->get_component_name(), schedule_comp);
        return true;
    }

    bool CConnectionObject::set_tcp_connection(boost::asio::ip::tcp::socket socket) {
        if (m_tcp_socket_ptr && m_tcp_socket_ptr->is_open()) {
            m_tcp_socket_ptr->close();
        }

        m_tcp_socket_ptr = std::make_shared<boost::asio::ip::tcp::socket>(std::move(socket));

        // set keep alive
        boost::asio::socket_base::keep_alive alive_option(true);
        m_tcp_socket_ptr->set_option(alive_option);
        return true;
    }

    bool CConnectionObject::set_udp_connection(boost::asio::ip::udp::socket &socket) {
        if (m_udp_socket_ptr) {
            if (m_udp_socket_ptr->is_open()) {
            m_udp_socket_ptr->close();
            }
        }

        m_udp_socket_ptr.reset(&socket);
        return true;
    }
}