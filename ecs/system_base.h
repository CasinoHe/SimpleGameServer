// Purpose: Entity-Component-System header for Base Systems
// Data: 2019.3.8
// By: Casino

#pragma once

#include <boost/noncopyable.hpp>

#include <memory>

namespace simple_server
{
namespace ecs
{

class CWorldBase;

class CSystemBase : boost::noncopyable
{
public:
  CSystemBase();
  virtual ~CSystemBase();

  inline bool is_enabled() { return m_is_enabled; }
  inline bool enable() { m_is_enabled = true; }
  inline bool disable() { m_is_enabled = false; }
  virtual bool configure(std::shared_ptr<CWorldBase> wolrd_ptr);
  virtual bool unconfigure();

private:
  bool m_is_enabled;
  bool m_is_configured;
  std::shared_ptr<CWorldBase> m_world_ptr;
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

} // namespace ecs
} // namespace simple_server