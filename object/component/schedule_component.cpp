// Purpose: Schedule component for Connection
// Date: 2019.2.25
// By: CasinoHe

#include "object/component/schedule_component.h"
#include "object/component_names.h"

#include <iostream>

namespace simple_server {
    CScheduleComponent::CScheduleComponent(std::shared_ptr<CGameObject> obj_ptr):
        CGameObjectComponent(obj_ptr, SCHEDULE_COMPONENT_NAME) {
            // clear schedule list
            m_schedule_list.clear();
    }

    CScheduleComponent::~CScheduleComponent() {

    }

    void CScheduleComponent::on_timer() {
        std::cout << "schedule on timer" << std::endl;
    }
}