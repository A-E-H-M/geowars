#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

#include "geowars/entity_manager.hpp"
#include "geowars/entity.hpp"

using namespace GWars;

TEST_CASE("EntityManager constructor", "[entity_manager]") {
    SECTION("EntityManager initializes correctly") {
        EntityManager manager;
        REQUIRE(manager.getEntities().empty());
    }
}

TEST_CASE("EntityManager addEntity", "[entity_manager]") {
    SECTION("addEntity creates new entity with correct tag") {
        EntityManager manager;
        auto entity = manager.addEntity("player");
        
        REQUIRE(entity != nullptr);
        REQUIRE(entity->tag() == "player");
        REQUIRE(entity->isActive() == true);
        REQUIRE(entity->id() == 0); // First entity should have ID 0
    }
    
    SECTION("addEntity creates entities with incrementing IDs") {
        EntityManager manager;
        auto entity1 = manager.addEntity("player");
        auto entity2 = manager.addEntity("enemy");
        auto entity3 = manager.addEntity("bullet");
        
        REQUIRE(entity1->id() == 0);
        REQUIRE(entity2->id() == 1);
        REQUIRE(entity3->id() == 2);
    }
    
    SECTION("addEntity with different tags") {
        EntityManager manager;
        auto player = manager.addEntity("player");
        auto enemy = manager.addEntity("enemy");
        auto bullet = manager.addEntity("bullet");
        
        REQUIRE(player->tag() == "player");
        REQUIRE(enemy->tag() == "enemy");
        REQUIRE(bullet->tag() == "bullet");
    }
}

TEST_CASE("EntityManager update", "[entity_manager]") {
    SECTION("update adds entities to main vector") {
        EntityManager manager;
        auto entity1 = manager.addEntity("player");
        auto entity2 = manager.addEntity("enemy");
        
        // Entities should not be in main vector until update is called
        REQUIRE(manager.getEntities().empty());
        
        manager.update();
        
        // After update, entities should be in main vector
        REQUIRE(manager.getEntities().size() == 2);
    }
    
    SECTION("update removes dead entities") {
        EntityManager manager;
        auto entity1 = manager.addEntity("player");
        auto entity2 = manager.addEntity("enemy");
        
        manager.update();
        REQUIRE(manager.getEntities().size() == 2);
        
        // Destroy one entity
        entity1->destroy();
        REQUIRE_FALSE(entity1->isActive());
        
        manager.update();
        REQUIRE(manager.getEntities().size() == 1);
        
        // The remaining entity should be entity2
        REQUIRE(manager.getEntities()[0]->tag() == "enemy");
    }
    
    SECTION("update clears entities to add after processing") {
        EntityManager manager;
        manager.addEntity("player");
        manager.addEntity("enemy");
        
        manager.update();
        
        // Add more entities after update
        manager.addEntity("bullet");
        manager.update();
        
        REQUIRE(manager.getEntities().size() == 3);
    }
}

TEST_CASE("EntityManager getEntities", "[entity_manager]") {
    SECTION("getEntities returns all entities") {
        EntityManager manager;
        auto entity1 = manager.addEntity("player");
        auto entity2 = manager.addEntity("enemy");
        auto entity3 = manager.addEntity("bullet");
        
        manager.update();
        
        const auto& entities = manager.getEntities();
        REQUIRE(entities.size() == 3);
        
        // Check that all entities are present
        bool hasPlayer = false, hasEnemy = false, hasBullet = false;
        for (const auto& entity : entities) {
            if (entity->tag() == "player") hasPlayer = true;
            if (entity->tag() == "enemy") hasEnemy = true;
            if (entity->tag() == "bullet") hasBullet = true;
        }
        REQUIRE(hasPlayer);
        REQUIRE(hasEnemy);
        REQUIRE(hasBullet);
    }
    
    SECTION("getEntities by tag returns correct entities") {
        EntityManager manager;
        auto player1 = manager.addEntity("player");
        auto player2 = manager.addEntity("player");
        auto enemy1 = manager.addEntity("enemy");
        auto enemy2 = manager.addEntity("enemy");
        auto bullet = manager.addEntity("bullet");
        
        manager.update();
        
        const auto& players = manager.getEntities("player");
        const auto& enemies = manager.getEntities("enemy");
        const auto& bullets = manager.getEntities("bullet");
        
        REQUIRE(players.size() == 2);
        REQUIRE(enemies.size() == 2);
        REQUIRE(bullets.size() == 1);
        
        // Verify correct entities are returned
        for (const auto& entity : players) {
            REQUIRE(entity->tag() == "player");
        }
        for (const auto& entity : enemies) {
            REQUIRE(entity->tag() == "enemy");
        }
        for (const auto& entity : bullets) {
            REQUIRE(entity->tag() == "bullet");
        }
    }
    
    SECTION("getEntities by tag with non-existent tag") {
        EntityManager manager;
        manager.addEntity("player");
        manager.update();
        
        const auto& nonExistent = manager.getEntities("nonexistent");
        REQUIRE(nonExistent.empty());
    }
}

TEST_CASE("EntityManager removeDeadEntities integration", "[entity_manager]") {
    SECTION("removeDeadEntities works with mixed alive and dead entities") {
        EntityManager manager;
        auto entity1 = manager.addEntity("player");
        auto entity2 = manager.addEntity("enemy");
        auto entity3 = manager.addEntity("enemy");
        auto entity4 = manager.addEntity("bullet");
        
        manager.update();
        REQUIRE(manager.getEntities().size() == 4);
        REQUIRE(manager.getEntities("enemy").size() == 2);
        
        // Destroy some entities
        entity1->destroy(); // player
        entity3->destroy(); // one enemy
        
        manager.update();
        
        // Check main vector
        REQUIRE(manager.getEntities().size() == 2);
        
        // Check tagged vectors
        REQUIRE(manager.getEntities("player").size() == 0);
        REQUIRE(manager.getEntities("enemy").size() == 1);
        REQUIRE(manager.getEntities("bullet").size() == 1);
        
        // Verify remaining entities are correct
        REQUIRE(manager.getEntities("enemy")[0]->id() == entity2->id());
        REQUIRE(manager.getEntities("bullet")[0]->id() == entity4->id());
    }
    
    SECTION("removeDeadEntities handles all entities destroyed") {
        EntityManager manager;
        auto entity1 = manager.addEntity("player");
        auto entity2 = manager.addEntity("enemy");
        
        manager.update();
        REQUIRE(manager.getEntities().size() == 2);
        
        // Destroy all entities
        entity1->destroy();
        entity2->destroy();
        
        manager.update();
        
        REQUIRE(manager.getEntities().size() == 0);
        REQUIRE(manager.getEntities("player").size() == 0);
        REQUIRE(manager.getEntities("enemy").size() == 0);
    }
}

TEST_CASE("EntityManager stress test", "[entity_manager]") {
    SECTION("handles many entities efficiently") {
        EntityManager manager;
        
        // Add many entities
        std::vector<std::shared_ptr<Entity>> entities;
        for (int i = 0; i < 100; ++i) {
            std::string tag = (i % 3 == 0) ? "player" : (i % 3 == 1) ? "enemy" : "bullet";
            entities.push_back(manager.addEntity(tag));
        }
        
        manager.update();
        REQUIRE(manager.getEntities().size() == 100);
        
        // Destroy every other entity
        for (size_t i = 0; i < entities.size(); i += 2) {
            entities[i]->destroy();
        }
        
        manager.update();
        REQUIRE(manager.getEntities().size() == 50);
        
        // Verify all remaining entities are active
        for (const auto& entity : manager.getEntities()) {
            REQUIRE(entity->isActive());
        }
    }
}