// Purpose: Entity-Component-System header for Base Entity
// Data: 2019.3.8
// By: Casino

#include "ecs/entity_base.h"

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_serialize.hpp>
#include <boost/uuid/uuid_io.hpp>

namespace simple_server
{
namespace ecs
{

CEntityBase::CEntityBase(const std::string &entityid)
{
  if (entityid.empty())
  {
    boost::uuids::uuid tag = boost::uuids::random_generator()();
    m_entityid_str = boost::uuids::to_string(tag);
  }
  else
  {
    m_entityid_str = entityid;
  }

  m_world_ptr = nullptr;
}

CEntityBase::~CEntityBase()
{
}

bool CEntityBase::join_world(std::shared_ptr<CWorldBase> world_ptr)
{
  if (m_world_ptr)
  {
    return false;
  }
  else
  {
    m_world_ptr = world_ptr;
    return true;
  }
}

bool CEntityBase::detach_from_world()
{
  if (!m_world_ptr)
  {
    return false;
  }

  m_world_ptr = nullptr;
  return true;
}

bool CEntityBase::before_destroy()
{
  // release all component
  m_components_map.clear();

  // release world ptr
  detach_from_world();

  return true;
}

} // namespace ecs
} // namespace simple_server