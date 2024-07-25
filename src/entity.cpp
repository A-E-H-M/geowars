#include "../include/geowars/entity.h"
#include <string>
//#include <SFML/Graphics.hpp>

Entity::Entity()
{
	//maybe write an exception handler for this
}

Entity::Entity(const size_t id, const std::string & tag)
{
	m_id = id;
	m_tag = tag;
}

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

const std::string& Entity::tag() const
{
	return m_tag;
}

//const size_t Entity::id() const
size_t Entity::id() const
{
	return m_id;
}

void Entity::destroy()
{
	m_active = false;
}
