// Purpose: Schedule component for Connection
// Date: 2019.2.25
// By: CasinoHe

#include "object/connection/conn_schedule_component.h"

namespace simple_server {
    CConnectionScheduleComponent::CConnectionScheduleComponent(boost::shared_ptr<CGameObject> obj_ptr, const std::string &name):
        CGameObjectComponent(obj_ptr, name) {
    }

    CConnectionScheduleComponent::~CConnectionScheduleComponent() {

    }
}