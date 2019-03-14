// Purpose: Entity-Component-System header for Base Systems
// Data: 2019.3.8
// By: Casino

#pragma once

#ifdef ECS_USE_LOG
#include "log/log.h"
#endif

#include <boost/noncopyable.hpp>

#include <memory>
#include <iostream>
#include <functional>

namespace simple_server
{
namespace ecs
{

class CWorldBase;
class CEventBase;

class CSystemBase : boost::noncopyable
{
public:
  CSystemBase();
  virtual ~CSystemBase();

  inline bool is_enabled() { return m_is_enabled; }
  inline void enable() { m_is_enabled = true; }
  inline void disable() { m_is_enabled = false; }
  virtual bool configure(std::shared_ptr<CWorldBase> wolrd_ptr);
  virtual bool unconfigure();
  virtual void frame_tick(std::shared_ptr<CWorldBase>, CEventBase &event);

  template <typename EventType>
  void on_event(std::shared_ptr<CWorldBase> world_ptr, EventType &event);

  template <typename EventType>
  bool register_event_handler(std::function<void (std::shared_ptr<CWorldBase>, CEventBase &)>);
  template <typename EventType>
  bool unregister_event_handler();

  // particularly, there is a frame tick handler for tick event
  template <typename T>
  void register_frame_tick_handler();

private:
  bool m_is_enabled;
  bool m_is_configured;
  std::shared_ptr<CWorldBase> m_world_ptr;
  std::unordered_map<size_t, std::function<void (std::shared_ptr<CWorldBase>, CEventBase &)>> m_event_handler_map;
};

CSystemBase::CSystemBase()
{
  m_world_ptr = nullptr;
  m_is_enabled = false;
  m_is_configured = false;
}

CSystemBase::~CSystemBase()
{
  m_is_enabled = false;
  m_world_ptr = nullptr;
}

bool CSystemBase::configure(std::shared_ptr<CWorldBase> world_ptr)
{
  if (m_is_configured)
  {
    return false;
  }

  m_is_configured = true;
  m_world_ptr = world_ptr;
}

bool CSystemBase::unconfigure()
{
  if (!m_is_configured)
  {
    return false;
  }

  m_is_configured = false;
  m_world_ptr = nullptr;
  return true;
}

void CSystemBase::frame_tick(std::shared_ptr<CWorldBase> world_ptr, CEventBase &event)
{
  return;
}

template <typename EventType>
void CSystemBase::on_event(std::shared_ptr<CWorldBase> world_ptr, EventType &event)
{
  size_t hash = typeid(EventType).hash_code();
  auto iter = m_event_handler_map.find(hash);
  if (iter == m_event_handler_map.end())
  {
#ifdef ECS_USE_LOG
    LOG_WARNING(g_logger) << "System cannot find handler for " << typeid(EventType).name();
#else
    std::cout << "System cannot find handler for " << typeid(EventType).name() << std::endl;
#endif
    return;
  }

  auto function = iter->second;
  function(world_ptr, dynamic_cast<CEventBase>(event));
  return;
}

template <typename EventType>
bool CSystemBase::register_event_handler(std::function<void (std::shared_ptr<CWorldBase>, CEventBase &)> function)
{
  size_t hash = typeid(EventType).hash_code();
  auto iter = m_event_handler_map.find(hash);
  if (iter != m_event_handler_map.end())
  {
    return false;
  }

  m_event_handler_map[hash] = function;
  return true;
}

template <typename EventType>
bool CSystemBase::unregister_event_handler()
{
  size_t hash = typeid(EventType).hash_code();
  return 1 == m_event_handler_map.erase(hash);
}

template <typename T>
void CSystemBase::register_frame_tick_handler()
{
  std::function<void (std::shared_ptr<CWorldBase>, CEventBase &)> function = std::bind(&T::frame_tick, this, std::placeholders::_1, std::placeholders::_2);
  register_event_handler<CTickEvent>(function);
}

} // namespace ecs
} // namespace simple_server