#include "geowars/movement.hpp"
#include "geowars/game.hpp"

namespace GWars
{
    // Implement player movement
    void Movement::inputMovement(Game& game)
    {
        if (game.m_player->cInput->up) {
            game.m_player->cTransform->velocity.y = game.m_playerConfig.speed_max * -1;
        }
        if (game.m_player->cInput->down) {
            game.m_player->cTransform->velocity.y = game.m_playerConfig.speed_max;
        }
        if (game.m_player->cInput->left) {
            game.m_player->cTransform->velocity.x = game.m_playerConfig.speed_max * -1;
        }
        if (game.m_player->cInput->right) {
        game.m_player->cTransform->velocity.x = game.m_playerConfig.speed_max;
        }
    }

    // Movement speed update
    void Movement::updateSpeed(Game& game)
    {
        for (auto& e : game.m_entities.getEntities())
        {
            e->cTransform->pos.x += e->cTransform->velocity.x;
            e->cTransform->pos.y += e->cTransform->velocity.y;
        }

        game.m_player->cTransform->velocity = { 0, 0 };
    }

    void Movement::updatePlayer(Game& game)
    {
        updateSpeed(game);
        inputMovement(game);
    }
}