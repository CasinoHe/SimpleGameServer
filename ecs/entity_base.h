// Purpose: Entity-Component-System header for Base Entity
// Data: 2019.3.8
// By: Casino

#pragma once

#include <unordered_map>
#include <memory>
#include <iostream>
#include <string>

#include <boost/noncopyable.hpp>

namespace simple_server
{
namespace ecs
{

class CEntityBase;
class CWorldBase;

template <typename T>
class CComponentWrapper : public boost::noncopyable
{
public:
  CComponentWrapper(std::shared_ptr<T> component);
  virtual ~CComponentWrapper();

  std::shared_ptr<T> get() { return m_component_ptr; }

private:
  std::shared_ptr<T> m_component_ptr;
};

class CEntityBase : public boost::noncopyable
{
public:
  CEntityBase(const std::string &entityid);
  virtual ~CEntityBase();

  const std::string &get_entityid() {return m_entityid_str;}

  // interface for component
  template <typename T, typename... Types>
  std::shared_ptr<T> new_component(Types... data);
  template <typename T>
  bool add_component(std::shared_ptr<T> component);
  template <typename T>
  bool remove_component();
  template <typename T>
  std::shared_ptr<T> get_component();

  // join world or detach from world
  bool join_world(std::shared_ptr<CWorldBase> world_ptr);
  bool detach_from_world();

  virtual bool before_destruct();

private:
  std::unordered_map<size_t, std::shared_ptr<void>> m_components_map;
  std::string m_entityid_str;
  std::shared_ptr<CWorldBase> m_world_ptr;
};

// function definition
template <typename T>
CComponentWrapper<T>::CComponentWrapper(std::shared_ptr<T> component)
{
  m_component_ptr = component;
}

template <typename T>
CComponentWrapper<T>::~CComponentWrapper()
{
}

template <typename T, typename... Types>
std::shared_ptr<T> CEntityBase::new_component(Types... data)
{
  std::shared_ptr<T> component_ptr = std::make_shared<T>(data...);
  if (add_component<T>(component_ptr))
  {
    return component_ptr;
  }
  else
  {
    return nullptr;
  }
}

template <typename T>
bool CEntityBase::add_component(std::shared_ptr<T> component)
{
  if (!component)
  {
    return false;
  }

  size_t hash = typeid(T).hash_code();

  auto iter = m_components_map.find(hash);
  if (iter != m_components_map.end())
  {
    return false;
  }

  std::shared_ptr<CComponentWrapper<T>> comp_wrapper_ptr = std::make_shared<CComponentWrapper<T>>(component);
  m_components_map[hash] = std::reinterpret_pointer_cast<void>(comp_wrapper_ptr);
  return true;
}

template <typename T>
bool CEntityBase::remove_component()
{
  size_t hash = typeid(T).hash_code();

  auto iter = m_components_map.find(hash);
  if (iter == m_components_map.end())
  {
    return false;
  }

  m_components_map.erase(iter);
  return true;
}

template <typename T>
std::shared_ptr<T> CEntityBase::get_component()
{
  size_t hash = typeid(T).hash_code();

  auto iter = m_components_map.find(hash);
  if (iter == m_components_map.end())
  {
    return nullptr;
  }

  auto wrapper_ptr = std::reinterpret_pointer_cast<CComponentWrapper<T>>(iter->second);
  return wrapper_ptr->get();
}

} // namespace ecs
} // namespace simple_server