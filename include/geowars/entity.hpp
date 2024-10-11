#pragma once

#include "components.hpp"
#include <memory>
#include <string>

class Entity
{
	private:

		friend class EntityManager;

		bool m_active = true;			// Used to assess if entity is active
		size_t m_id = 0;				// Entity ID
		std::string m_tag = "default";	// Entity tag used for adding to the correct entity vector in map of entities

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
