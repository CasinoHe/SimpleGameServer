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
}

CEntityBase::~CEntityBase()
{
}

} // namespace ecs
} // namespace simple_server