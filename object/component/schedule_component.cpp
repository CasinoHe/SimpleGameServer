// Purpose: Schedule component for Connection
// Date: 2019.2.25
// By: CasinoHe

#include "object/component/schedule_component.h"

namespace simple_server {
    CScheduleComponent::CScheduleComponent(boost::shared_ptr<CGameObject> obj_ptr):
        CGameObjectComponent(obj_ptr, "ConnectionSchedule") {
            // clear schedule list
            m_schedule_list.clear();
    }

    CScheduleComponent::~CScheduleComponent() {

    }
}