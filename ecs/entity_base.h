// Purpose: Entity-Component-System header for Base Entity
// Data: 2019.3.8
// By: Casino

#pragma once

#include <unordered_map>

#include <boost/shared_ptr.hpp>

namespace simple_server {
    namespace ecs {
        template<typename T>
        class CComponentWrapper {
            private:
                boost::shared_ptr<T> m_component_ptr;
        };

        class CEntityBase {
        };
    }
}