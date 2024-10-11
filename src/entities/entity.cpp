#include "../include/geowars/entity.hpp"
#include <string>

Entity::Entity()
{
	// TODO: Write an exception handler for this
}

// Initalize an entity with an ID and tag
Entity::Entity(const size_t id, const std::string & tag)
{
	m_id = id;
	m_tag = tag;
}

// Get the entity's state 
bool Entity::isActive() const
{
	if (m_active)
	{
		return true;
	}
	else 
	{
		return false;
	}
}

// Get the entity's tag
const std::string& Entity::tag() const
{
	return m_tag;
}

// Get the entity's ID
//const size_t Entity::id() const
size_t Entity::id() const
{
	return m_id;
}

// Update the entity's state to false
void Entity::destroy()
{
	m_active = false;
}
