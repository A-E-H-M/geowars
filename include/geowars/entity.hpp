#pragma once

#include <memory>
#include <string>

#include "geowars/components.hpp"

class Entity
{
	private:
		Entity(const size_t id, const std::string& tag) : m_id(id), m_tag(tag) {};
		
		bool m_active{true};			// Used to assess if entity is active
		const size_t m_id;				// Entity ID
		const std::string m_tag;	// Entity tag used for adding to the correct entity vector in map of entities

	public:
		friend class EntityManager;

		// Component pointers to the class type from component.h
		std::shared_ptr<CTransform> cTransform;
		std::shared_ptr<CShape> cShape;
		std::shared_ptr<CCollision> cCollision;
		std::shared_ptr<CInput> cInput;
		std::shared_ptr<CScore> cScore;
		std::shared_ptr<CLifespan> cLifespan;

		// Private member access functions
		bool isActive() const;
		const std::string& tag() const;
		size_t id() const;
		void destroy();
};
