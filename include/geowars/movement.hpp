#pragma once

#include "geowars/entity_manager.hpp"
#include "geowars/entity.hpp"

namespace GWars
{
    class Movement
    {
        private:
            void inputMovement(std::shared_ptr<Entity>& player);
            void updatePosition(const std::shared_ptr<Entity>& e);
            void updateRotation(const std::shared_ptr<Entity>& e);
            void updatePlayerVel(std::shared_ptr<Entity>& e);

        public:
            Movement(){};
            void updatePlayerMov(std::shared_ptr<Entity>& player);
            void updateEntitiesPos(EntityManager& entityManager);
            void updateEntitiesMov(EntityManager& entityManager);
    };
}