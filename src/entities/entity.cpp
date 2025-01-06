#include <string>

#include "geowars/entity.hpp"

// Get the entity's state 
bool Entity::isActive() const
{
	return m_active;
}

// Get the entity's tag
const std::string& Entity::tag() const
{
	return m_tag;
}

// Get the entity's ID
size_t Entity::id() const
{
	return m_id;
}

// Update the entity's state to false
void Entity::destroy()
{
	m_active = false;
}
