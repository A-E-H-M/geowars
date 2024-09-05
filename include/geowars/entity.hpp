#pragma once

#include "components.h"
#include <memory>
#include <string>

class Entity
{
	friend class EntityManager;

	bool		m_active	= true;
	size_t		m_id		= 0;
	std::string	m_tag		= "default";

public:
	
	// Component pointers to the class type from component.h
	std::shared_ptr<CTransform> cTransform;
	std::shared_ptr<CShape> cShape;
	std::shared_ptr<CCollision> cCollision;
	std::shared_ptr<CInput> cInput;
	std::shared_ptr<CScore> cScore;
	std::shared_ptr<CLifespan> cLifespan;

	// Private member access functions
	bool isActive() const;
	const std::string & tag() const;
	size_t id() const;
	//const size_t id() const;
	
	void destroy();
	
	// TODO: Re-establish constructor and destructor as private following testing
	Entity();
	Entity(const size_t id, const std::string & tag);	
};
