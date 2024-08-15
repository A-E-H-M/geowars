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

	//constructor and destructor - make sure declare as private as soon as running
		//Entity();
		//Entity(const size_t id, const std::string& tag);

public:
	Entity();
	Entity(const size_t id, const std::string & tag);

	//component pointers to the class type from component.h
	std::shared_ptr<CTransform> cTransform;
	std::shared_ptr<CShape> cShape;
	std::shared_ptr<CCollision> cCollision;
	std::shared_ptr<CInput> cInput;
	std::shared_ptr<CScore> cScore;
	std::shared_ptr<CLifespan> cLifespan;

	//private member access functions
	bool isActive() const;
	const std::string & tag() const;
	//const size_t id() const;
	size_t id() const;
	void destroy();

};
