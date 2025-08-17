#pragma once

#include <vector>
#include <map>
#include <string>
#include <string_view>

#include "geowars/entity.hpp"

namespace GWars
{
	using EntityVec = std::vector<std::shared_ptr<Entity>>;
	using EntityMap = std::map<std::string, EntityVec>;

	class EntityManager
	{	
		private:
			EntityVec m_entities;			// Vector of all active entities
			EntityVec m_entitiesToAdd;		// Vector of entities to add
			EntityMap m_entityMap;			// Map of separate entities vectors by tag
			size_t m_totalEntities{0};		// Count of all entities initialized throughout game
			
			// Remove deactivated entities from vector of active entities
			void removeDeadEntities(EntityVec& vec);

		public:	
			EntityManager(){};

			// Entity management tools
			void update();
			std::shared_ptr<Entity> addEntity(std::string_view tag);
		
			const EntityVec& getEntities();
			const EntityVec& getEntities(std::string tag);

			// TODO: Test and evaluate the following
			// const std::map<std::string, EntityVec> & getEntityMap(const std::string& tag);
	};
} // End namespace
