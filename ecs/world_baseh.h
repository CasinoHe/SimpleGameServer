// Purpose: Entity-Component-System header for Base world
// Data: 2019.3.8
// By: Casino

#pragma once

#include "ecs/system_base.h"
#include "ecs/entity_base.h"
#include "ecs/event_base.hpp"
#include "ecs/system_base.h"

#ifdef ECS_USE_LOG
#include "log/log.h"
#endif

#include <memory>
#include <iostream>
#include <list>
#include <string>
#include <algorithm>

#include <boost/noncopyable.hpp>

namespace simple_server
{
namespace ecs
{

class CWorldBase : public boost::noncopyable, public std::enable_shared_from_this<CWorldBase>
{
public:
  typedef std::shared_ptr<CWorldBase> world_ptr;

  CWorldBase();
  virtual ~CWorldBase();

  template <typename T>
  bool register_system();
  template <typename T>
  bool unregister_system();
  template <typename T>
  bool enable_system();
  template <typename T>
  bool disable_system();

  // called by environment tick function
  // tick every frame
  void frame_tick();

  template <typename SystemType, typename EventType>
  bool subscribe();
  template <typename EventType>
  bool subscribe_one(CSystemBase::system_ptr_type &system_ptr);

  template <typename SystemType, typename EventType>
  bool unsubscribe();
  bool unsubscribe_one(std::list<CSystemBase::system_ptr_type> &system_list_ptr, CSystemBase::system_ptr_type system_ptr);

  template <typename EntityType>
  std::shared_ptr<EntityType> create_entity(std::string &entityid);
  template <typename EntityType>
  std::shared_ptr<EntityType> create_entity(const char *entityid);
  bool destroy_entity(std::string &entityid);

  // emit event
  template <typename EventType>
  void emit(EventType &event);

protected:
  template <typename T>
  std::shared_ptr<T> get_system();

private:
  std::unordered_map<size_t, std::shared_ptr<CSystemBase>> m_systems_map;
  std::unordered_map<std::string, std::shared_ptr<CEntityBase>> m_entities_map;
  std::unordered_map<size_t, std::list<CSystemBase::system_ptr_type>> m_subscribed_event_map;
};

CWorldBase::CWorldBase()
{
  m_systems_map.clear();
  m_entities_map.clear();
}

CWorldBase::~CWorldBase()
{
  m_systems_map.clear();
  m_entities_map.clear();
}

template <typename T>
bool CWorldBase::register_system()
{
  size_t hash = typeid(T).hash_code();
  auto iter = m_systems_map.find(hash);
  if (iter != m_systems_map.end())
  {
    return false;
  }

  std::shared_ptr<T> system = std::make_shared<T>();
  m_systems_map[hash] = std::dynamic_pointer_cast<CSystemBase>(system);

  system->configure(shared_from_this());
  return true;
}

template <typename T>
bool CWorldBase::unregister_system()
{
  size_t hash = typeid(T).hash_code();
  auto iter = m_systems_map.find(hash);

  if (iter == m_systems_map.end())
  {
    return false;
  }

  auto system = iter->second;
  m_systems_map.erase(iter);
  system->unconfigure();
  return true;
}

template <typename T>
bool CWorldBase::enable_system()
{
  std::shared_ptr<T> system_ptr = get_system<T>();
  if (!system_ptr)
  {
    return false;
  }

  if (system_ptr->is_enabled())
  {
    return false;
  }

  system_ptr->enable();
  return true;
}

template <typename T>
bool CWorldBase::disable_system()
{
  std::shared_ptr<T> system_ptr = get_system<T>();
  if (!system_ptr)
  {
    return false;
  }

  if (!system_ptr->is_enabled())
  {
    return false;
  }
  system_ptr->disable();
  return true;
}

template <typename T>
std::shared_ptr<T> CWorldBase::get_system()
{
  size_t hash = typeid(T).hash_code();
  auto iter = m_systems_map.find(hash);

  if (iter == m_systems_map.end())
  {
    return nullptr;
  }

  return std::dynamic_pointer_cast<T>(iter->second);
}

void CWorldBase::frame_tick()
{
  CTickEvent event;
  emit<CTickEvent>(event);
}

template <typename SystemType, typename EventType>
bool CWorldBase::subscribe()
{
  // find system first
  CSystemBase::system_ptr_type system_ptr = get_system<SystemType>();
  if (!system_ptr)
  {
    return false;
  }

  subscribe_one<EventType>(system_ptr);
  return true;
}

template <typename EventType>
bool CWorldBase::subscribe_one(CSystemBase::system_ptr_type &system_ptr)
{
  if (!system_ptr)
  {
    return false;
  }

  size_t event_hash = typeid(EventType).hash_code();
  auto event_iter = m_subscribed_event_map.find(event_hash);

  if (event_iter == m_subscribed_event_map.end())
  {
    m_subscribed_event_map[event_hash] = std::list<CSystemBase::system_ptr_type>();
    m_subscribed_event_map[event_hash].emplace_back(system_ptr);
    return true;
  }
  else
  {
    auto &system_ptr_list = m_subscribed_event_map[event_hash];
    auto system_iter = std::find(system_ptr_list.cbegin(), system_ptr_list.cend(), system_ptr);

    if (system_iter == system_ptr_list.cend())
    {
      m_subscribed_event_map[event_hash].emplace_back(system_ptr);
      return true;
    }
  }

  // if system has subscribed such event
  // return true
  return true;
}

template <typename SystemType, typename EventType>
bool CWorldBase::unsubscribe()
{
  size_t event_hash = typeid(EventType).hash_code();
  auto iter = m_subscribed_event_map.find(event_hash);
  if (iter == m_subscribed_event_map.end())
  {
    return false;
  }

  auto &system_list_ptr = iter->second;

  // find system_ptr
  auto system_ptr = get_system<SystemType>();
  if (!system_ptr)
  {
    return false;
  }

  return unsubscribe_one(system_list_ptr, system_ptr);
}

bool unsubscribe_one(std::list<CSystemBase::system_ptr_type> &system_list_ptr, CSystemBase::system_ptr_type system_ptr)
{
  if (system_list_ptr.empty())
  {
    return false;
  }

  // delete ptr from ptr list
  for (auto iter = system_list_ptr.cbegin(); iter != system_list_ptr.end(); iter++)
  {
    if (*iter == system_ptr)
    {
      iter = system_list_ptr.erase(iter);
      return true;
    }
  }

  return false;
}

template <typename EventType>
void CWorldBase::emit(EventType &pevent)
{
  // find system which subscribed this event
  size_t event_hash = typeid(EventType).hash_code();
  auto event_iter = m_subscribed_event_map.find(event_hash);
  if (event_iter == m_subscribed_event_map.end())
  {
    return;
  }

  for (auto &item: event_iter->second)
  {
    if (!item->is_enabled())
    {
      continue;
    }

    try
    {
      item->on_event<EventType>(shared_from_this(), pevent);
    }
    catch (std::exception &e)
    {
#ifdef ECS_USE_LOG
      LOG_WARNING(g_logger) << "Event Except from " << typeid(EventType).name();
      LOG_WARNING(g_logger) << "info: " << e.what();
#else
      std::cout << "Event Except from " << typeid(EventType).name() << std::endl;
      std::cout << "info: " << e.what() << std::endl;
#endif
      continue;
    }
  }
}

template <typename EntityType>
std::shared_ptr<EntityType> CWorldBase::create_entity(std::string &entityid)
{
  if (!entityid.empty())
  {
    auto iter = m_entities_map.find(entityid);
    if (iter != m_entities_map.end())
    {
      // entity exists already
      return nullptr;
    }
  }
  std::shared_ptr<EntityType> entity_ptr = std::make_shared<EntityType>(entityid);
  if (!entity_ptr)
  {
    return nullptr;
  }

  const std::string &des_entityid = entity_ptr->get_entityid();
  m_entities_map[des_entityid] = entity_ptr;

  // emit entity create event
  CEntityCreateEvent event(entity_ptr);
  emit<CEntityCreateEvent>(event);
  return entity_ptr;
}

template <typename EntityType>
std::shared_ptr<EntityType> CWorldBase::create_entity(const char *entityid)
{
  std::string entitystr(entityid);
  return create_entity<EntityType>(entitystr);
}

bool CWorldBase::destroy_entity(std::string &entityid)
{
  if (entityid.empty())
  {
    return false;
  }

  auto iter = m_entities_map.find(entityid);
  if (iter == m_entities_map.end())
  {
    return false;
  }

  int ret = m_entities_map.erase(entityid);
  if (ret == 1)
  {
    CEntityDestroyEvent event(iter->second);
    emit<CEntityDestroyEvent>(event);
    return true;
  }
  else {
    return false;
  }
}

} // namespace ecs
} // namespace simple_server