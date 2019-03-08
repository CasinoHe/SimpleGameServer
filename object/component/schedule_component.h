// Purpose: Schedule component for Connection
// Date: 2019.2.25
// By: CasinoHe
#pragma once
#ifndef SIMPLE_SERVER_OBJECT_CONNECTION_CONN_SCHEDULE_COMPONENT_H
#define SIMPLE_SERVER_OBJECT_CONNECTION_CONN_SCHEDULE_COMPONENT_H


#include "schedule/schedule.h"
#include "object/game_object.h"
#include "object/game_object_component.h"

#include <list>
#include <string>
#include <memory>


namespace simple_server {
    class CGameObject;

    class CScheduleComponent : public CGameObjectComponent {
        private:
            std::list<SScheduleData> m_schedule_list;

        protected:
            virtual bool is_serializable() {return true;}

        public:
            CScheduleComponent(std::shared_ptr<CGameObject> obj_ptr);
            virtual ~CScheduleComponent();

            virtual void on_timer();
    };
} // namespace simple_server

#endif