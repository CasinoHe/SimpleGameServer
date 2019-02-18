// Purpose: Prepare for connection
// Date: 2019.02.16
// By: CasinoHe

#include "object/connection/connection_object.h"

namespace simple_server {
    CConnectionObject::CConnectionObject(const std::string &name, std::string object_id):
     CGameObject(name, object_id) {
         m_connect_time = boost::chrono::steady_clock::now();
    }

    CConnectionObject::~CConnectionObject() {

    }
}