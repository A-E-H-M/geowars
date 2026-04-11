#pragma once

#include "geowars/entity_manager.hpp"

namespace GWars
{
    class Collisions
    {
        public:
            Collisions(){};
            void updateCollisions(EntityManager& m_entity_manager, int& score);
    };
}