
#include "geowars/entity_manager.hpp"
#include "geowars/entity.hpp"
#include "geowars/movement.hpp"

namespace GWars
{
    // Implement player movement
    void Movement::inputMovement(std::shared_ptr<Entity>& player)
    {
        if (player->cInput->up) {
            player->cTransform->velocity.y = player->cTransform->speed.y * -1;
        }
        if (player->cInput->down) {
            player->cTransform->velocity.y = player->cTransform->speed.y;
        }
        if (player->cInput->left) {
            player->cTransform->velocity.x = player->cTransform->speed.x * -1;
        }
        if (player->cInput->right) {
            player->cTransform->velocity.x = player->cTransform->speed.x;
        }
    }

    void Movement::updatePlayerMov(std::shared_ptr<Entity>& player)
    {
        updatePlayerVel(player);
        inputMovement(player);
    }

    // Position of shape is based on the entity's transform->pos
    void Movement::updatePosition(const std::shared_ptr<Entity>& e)
    {
		e->cShape->circle.setPosition(e->cTransform->pos.x, e->cTransform->pos.y);
    }

    // Rotation of shape is based on the entity's transform->angle
    void Movement::updateRotation(const std::shared_ptr<Entity>& e)
    {
		e->cTransform->angle += 1.0f;
		e->cShape->circle.setRotation(e->cTransform->angle);
    }

    void Movement::updateEntitiesMov(EntityManager& entityManager)
    {
        for (const auto& e : entityManager.getEntities())
		{
            updatePosition(e);
            updateRotation(e);
        }
    }

    void Movement::updateEntitiesPos(EntityManager& entityManager)
    {
        for (const auto& e : entityManager.getEntities())
        {
            e->cTransform->pos.x += e->cTransform->velocity.x;
            e->cTransform->pos.y += e->cTransform->velocity.y;
        }
    }

    // Movement speed update
    void Movement::updatePlayerVel(std::shared_ptr<Entity>& player)
    {
        player->cTransform->velocity = { 0, 0 };
    }

}