#include "../include/geowars/entity_manager.h"

//#include <memory>
#include <vector>
#include <string>
//#include <bits/stdc++.h>
//#include <complex>
//#include <string_view>
//#include <iostream>
//#include <numeric>
#include <algorithm>

EntityManager::EntityManager()
{
}

void EntityManager::update()
{
	// TODO: add entities from m_entitiesToAdd the proper location(s)
	// 		 	- add them to the vector of all entities
	// 		 	- add them to the vector inside the map, with the tag as a key

	for (auto e : m_entitiesToAdd)
	{
		m_entities.push_back(e);
		m_entityMap[e->m_tag].push_back(e);
	}
	
	m_entitiesToAdd.clear();

	// remove dead entities from the vector of all entities
	removeDeadEntities(m_entities);

	// remove dead entities from each vector in the entity map
	// C++17 way of iterating through [key, value] pairs in a map
	for (auto& [t, vec]: m_entityMap){
		removeDeadEntities(vec);
	}
}


void EntityManager::removeDeadEntities(EntityVec & vec)
{
	// TODO: remove all dead entities from the input vector
	// 		 this is called by the update() function
	vec.erase(
		std::remove_if(
			vec.begin(), vec.end(), 
			[](std::shared_ptr<Entity> const e) { return e->isActive() == false; }),
	   		vec.end());

}

std::shared_ptr<Entity> EntityManager::addEntity(const std::string & tag)
{
	auto entity = std::shared_ptr<Entity>(new Entity(m_totalEntities, tag));

	m_entitiesToAdd.push_back(entity);

	return entity;
}

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
