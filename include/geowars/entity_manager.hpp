#pragma once

#include "entity.h"
#include <vector>
#include <map>

typedef std::vector<std::shared_ptr<Entity>> EntityVec;
typedef std::map<std::string, EntityVec>	 EntityMap;

class EntityManager {
	
	private:
		EntityVec	m_entities;				// Vector of all active entities
		EntityVec	m_entitiesToAdd;		// Vector of entities to add
		EntityMap	m_entityMap;			// Map of separate entities vectors by tag
		size_t		m_totalEntities = 0;	// Count of all entities intialized throughout game
		
		//	Remove deactived entities from vector of active entities
		void removeDeadEntities(EntityVec & vec);

	public:	
		// Entity management tools	
		void update();
		std::shared_ptr<Entity> addEntity(const std::string & tag);
	
		const EntityVec & getEntities();
		const EntityVec & getEntities(const std::string & tag);

		// TODO: Test and evaluate the following
		//const std::map<std::string, EntityVec> & getEntityMap(const std::string& tag);
	
		EntityManager();
};
