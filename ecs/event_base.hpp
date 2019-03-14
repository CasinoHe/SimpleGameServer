// Purpose: Entity-Component-System header for Base Events
// Data: 2019.3.8
// By: Casino

#pragma once

#include <memory>

#include <boost/noncopyable.hpp>

namespace simple_server
{
namespace ecs
{

class CEntityBase;

class CEventBase : public boost::noncopyable
{
};

class CTickEvent : public CEventBase
{
};

class CEntityCreateEvent : public CEventBase
{
public:
  CEntityCreateEvent(std::shared_ptr<CEntityBase> pointer) { m_entity_ptr = pointer; }
  std::shared_ptr<CEntityBase> m_entity_ptr;
};

class CEntityDestroyEvent : public CEventBase
{
public:
  CEntityDestroyEvent(std::shared_ptr<CEntityBase> pointer) { m_entity_ptr = pointer; }
  std::shared_ptr<CEntityBase> m_entity_ptr;
};

} // namespace ecs
} // namespace simple_server