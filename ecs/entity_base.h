// Purpose: Entity-Component-System header for Base Entity
// Data: 2019.3.8
// By: Casino

#pragma once

#include <unordered_map>
#include <memory>

#include <boost/noncopyable.hpp>

namespace simple_server
{
namespace ecs
{
class CEntityBase;

class CComponentWrapperBase
{
  public:
    CComponentWrapperBase();
    virtual ~CComponentWrapperBase();

    virtual void on_remove() = 0;
    virtual void on_assign() = 0;
};

template <typename T>
class CComponentWrapper : public CComponentWrapperBase
{
  public:
    CComponentWrapper(std::shared_ptr<T> component);

    virtual ~CComponentWrapper();
    virtual void on_remove();
    virtual void on_assign();

  private:
    std::shared_ptr<T> m_component_ptr;
};

class CEntityBase : public boost::noncopyable
{
  public:
    CEntityBase();
    virtual ~CEntityBase();

    // interface for component
    template<typename T, typename... Types>
    std::shared_ptr<T> new_component(Types ...data);
    template<typename T>
    bool add_component(std::shared_ptr<T> component);
    template<typename T>
    bool remove_component();
    template <typename T>
    std::shared_ptr<T> get_component();

  private:
    std::unordered_map<size_t, std::shared_ptr<CComponentWrapperBase>> m_components_map;
};

// function definition
CComponentWrapperBase::CComponentWrapperBase()
{
}

CComponentWrapperBase::~CComponentWrapperBase()
{
}

template<typename T>
CComponentWrapper<T>::CComponentWrapper(std::shared_ptr<T> component) : CComponentWrapperBase()
{
  m_component_ptr = component;
}

template<typename T>
CComponentWrapper<T>::~CComponentWrapper()
{
}

template<typename T>
void CComponentWrapper<T>::on_remove()
{
}

template<typename T>
void CComponentWrapper<T>::on_assign()
{
}

CEntityBase::CEntityBase()
{
}

CEntityBase::~CEntityBase()
{
}

template<typename T, typename... Types>
std::shared_ptr<T> CEntityBase::new_component(Types ...data)
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

template<typename T>
bool CEntityBase::add_component(std::shared_ptr<T> component)
{
  if (!component)
  {
    return false;
  }

  size_t hash = typeid(component).hash_code();
  auto iter = m_components_map.find(hash);
  if (iter != m_components_map.end())
  {
    return false;
  }

  std::shared_ptr<CComponentWrapper<T> > comp_wrapper_ptr = std::make_shared<CComponentWrapper<T> >(component);
  std::shared_ptr<CComponentWrapperBase> base_wrapper_ptr = std::dynamic_pointer_cast<CComponentWrapperBase>(comp_wrapper_ptr);

  m_components_map[hash] = base_wrapper_ptr;
  return true;
}

template<typename T>
bool CEntityBase::remove_component()
{
}

template<typename T>
std::shared_ptr<T> get_component()
{
}

} // namespace ecs
} // namespace simple_server