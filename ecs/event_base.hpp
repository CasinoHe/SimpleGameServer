// Purpose: Entity-Component-System header for Base Events
// Data: 2019.3.8
// By: Casino

#pragma once

#include <boost/noncopyable.hpp>

namespace simple_server
{
namespace ecs
{

class CEventBase : public boost::noncopyable
{
};

class CTickEvent: public CEventBase
{
};

} // namespace ecs
} // namespace simple_server