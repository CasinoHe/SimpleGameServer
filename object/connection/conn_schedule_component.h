// Purpose: Schedule component for Connection
// Date: 2019.2.25
// By: CasinoHe
#pragma once
#ifndef SIMPLE_SERVER_OBJECT_CONNECTION_CONN_SCHEDULE_COMPONENT_H
#define SIMPLE_SERVER_OBJECT_CONNECTION_CONN_SCHEDULE_COMPONENT_H


#include "object/game_object.h"
#include "schedule/schedule.h"
#include "object/game_object_component.h"

#include <list>
#include <string>

#include <boost/shared_ptr.hpp>

namespace simple_server {
    class CConnectionScheduleComponent : public CGameObjectComponent {
        private:
            std::list<SScheduleData> m_schedule_list;

        public:
            CConnectionScheduleComponent(boost::shared_ptr<CGameObject> obj_ptr, const std::string &name);
            virtual ~CConnectionScheduleComponent();
    };
} // namespace simple_server

#endif