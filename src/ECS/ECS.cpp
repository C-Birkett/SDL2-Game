#include "ECS.h"

//define 'Entity::addGroup' after the Manager is defined
void Entity::AddGroup(Group group)
{
  m_manager.AddToGroup(this, group);
  m_groupBitSet[group] = true;
}

void Entity::AddGroup(std::string group)
{
  m_manager.AddToGroup(this, group);
  m_groupBitSet[m_manager.GetGroup(group)] = true;
}
