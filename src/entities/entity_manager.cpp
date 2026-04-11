#include <vector>
#include <string>
#include <string_view>
#include <algorithm>

#include "geowars/entity_manager.hpp"

namespace GWars
{
	// Update entity vectors
	void EntityManager::update()
	{
		// TODO: Add entities to the vector of all entities & the vector inside the map, with the tag as a key
		for (const auto& e : m_entitiesToAdd)
		{
			m_entities.push_back(e);
			m_entityMap[e->m_tag].push_back(e);
		}
		
		m_entitiesToAdd.clear();

		// Remove dead entities from the vector of all entities
		removeDeadEntities(m_entities);

		// Remove dead entities from each vector in the entity map
		for (auto& [t, vec]: m_entityMap)
		{
			removeDeadEntities(vec);
		}

	}

	// Remove all dead entities from input vector
	void EntityManager::removeDeadEntities(EntityVec & vec) 
	{	
		vec.erase(
			std::remove_if(
				vec.begin(), vec.end(), 
				[](const std::shared_ptr<Entity>& e) { return !e->isActive(); }),
				vec.end());

	}

	// Add entity
	std::shared_ptr<Entity> EntityManager::addEntity(std::string_view tag)
	{
		auto entity = std::shared_ptr<Entity>(new Entity(m_totalEntities, tag));
		m_entitiesToAdd.push_back(entity);
		return entity;

	}

	// Get the vector of all entities
	const EntityVec& EntityManager::getEntities()
	{	
		return m_entities;
	}

	const EntityVec& EntityManager::getEntities(std::string tag)
	{	
		return m_entityMap.at(tag);
	}

} // End namespace