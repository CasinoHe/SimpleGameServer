// Purpose: Entity-Component-System header for Base world
// Data: 2019.3.8
// By: Casino

#pragma once

#include "ecs/system_base.h"
#include "ecs/entity_base.h"

#include <memory>

#include <boost/noncopyable.hpp>

namespace simple_server
{
namespace ecs
{

class CWorldBase : boost::noncopyable, std::enable_shared_from_this<CWorldBase>
{
public:
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

protected:
  template <typename T>
  std::shared_ptr<T> get_system();

private:
  std::unordered_map<size_t, std::shared_ptr<CSystemBase>> m_systems_map;
  std::unordered_map<std::string, std::shared_ptr<CEntityBase>> m_entities_map;
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

} // namespace ecs
} // namespace simple_server