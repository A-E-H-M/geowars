#include<string>

#include "geowars/collisions.hpp"
#include "geowars/game.hpp"

namespace GWars
{
	// Implement all collisions between entities
	void Collisions::updateCollisions(class Game& game)
	{
		for (const auto& e : game.m_entities.getEntities())
		{
			e->cCollision->boundingBox = e->cShape->circle.getGlobalBounds();
		}
		
		for (const auto& b : game.m_entities.getEntities("bullet"))
		{
			for (const auto& e : game.m_entities.getEntities("enemy"))
			{
				if (b->cCollision->boundingBox.intersects(e->cCollision->boundingBox))
				{
					e->destroy();
					b->destroy();
					game.m_score += 5;
				}
			} // End for loop
		} // End for loop
	};
} // End namespace