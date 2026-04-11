#include<string>

#include "geowars/collisions.hpp"
#include "geowars/entity_manager.hpp"

namespace GWars
{
	// Implement all collisions between entities
	void Collisions::updateCollisions(EntityManager& m_entity_manager, int& score)
	{
		for (const auto& e : m_entity_manager.getEntities())
		{
			e->cCollision->boundingBox = e->cShape->circle.getGlobalBounds();
		}
		
		for (const auto& b : m_entity_manager.getEntities("bullet"))
		{
			for (const auto& e : m_entity_manager.getEntities("enemy"))
			{
				if (b->cCollision->boundingBox.intersects(e->cCollision->boundingBox))
				{
					e->destroy();
					b->destroy();
					score += 5;
				}
			} // End for loop
		} // End for loop
	};
} // End namespace