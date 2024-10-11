#include "entity_manager.hpp"

#include <vector>
#include <string>
#include <algorithm>

EntityManager::EntityManager()
{
}

// Update entity vectors
void EntityManager::update()
{
	// TODO: Add entities to the vector of all entities & the vector inside the map, with the tag as a key
	for (auto e : m_entitiesToAdd)
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
			[](std::shared_ptr<Entity> const e) { return e->isActive() == false; }),
	   		vec.end());

}

// Add entity
std::shared_ptr<Entity> EntityManager::addEntity(const std::string & tag)
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

const EntityVec& EntityManager::getEntities(const std::string & tag)
{	
	// TODO: this is incorrect, return the correct vector from the map
	/*	
	for (auto& [t, vec]: m_entityMap){
		if (tag == t)
			//auto temp = vec;
			return vec;
	}
	//auto temp = m_entityMap.find(tag);
	*/
	return m_entityMap[tag];
}

/*
 const std::map<std::string, EntityVec> & EntityManager::getEntityMap(const std::string & tag)
{
	return m_entityMap[tag]; // This is not correct, it is a placeholder
}
*/
