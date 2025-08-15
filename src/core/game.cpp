#include <memory>
#include <cmath>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "geowars/config.hpp"
#include "geowars/game.hpp"
#include "geowars/window_manager.hpp"
#include "geowars/movement.hpp"
#include "geowars/collisions.hpp"

namespace GWars
{
	Game::Game(const configObject& gameConfig)
	{
		init(gameConfig);
	}

	void Game::init(const configObject& gameConfig)
	{	
		m_windowConfig = gameConfig.windowConfig;
		m_fontConfig = gameConfig.fontConfig;
		m_textConfig = gameConfig.textConfig;
		m_playerConfig = gameConfig.playerConfig;
		m_enemyConfig = gameConfig.enemyConfig;
		m_bulletConfig = gameConfig.bulletConfig;
		m_terrainConfig = gameConfig.terrainConfig;

		m_window_manager.initWindow(*this);

		// Set up score text
		m_text.setFont(m_font);
		m_text.setString(m_textConfig.text + std::to_string(0));
		m_text.setPosition(10, m_windowConfig.height - static_cast<float>(m_text.getCharacterSize()) - 10);

		// Load textures
		m_terrain.loadFromFile(m_terrainConfig.terrain_file_path);
		Terrain m_sceneBackground(m_terrainConfig.difficulty, m_terrainConfig.terrain_type, m_terrain);
		m_sceneBackgroundSprite.setTexture(m_terrain);

		// Spawn the player
		spawnPlayer();
	}

	void Game::run() {
		// Main while loop
		while (m_running)
		{
			m_entities.update();

			if (!m_paused)
			{
				sEnemySpawner();
				sLifespan();
				m_movement.updatePlayer(*this);
				//sCollision();
				m_collisions.updateCollisions(*this);
			}

			m_window_manager.pollWindowEvents(*this);
			sRender();

			m_currentFrame++;
		} // End main while loop

	}

	// Spawn player entity at the center of the window
	void Game::spawnPlayer() 
	{	
		// Create player entity
		auto entity = m_entities.addEntity(m_playerConfig.entity_type);

		// Player entity's spawning position based on window size
		//float mx = m_window.getSize().x / 2.0f;
		//float my = m_window.getSize().y / 2.0f;
		
		// Player entity's spawning position, speed, and rotation direction are from the configuration file
		entity->cTransform = std::make_shared<CTransform>(Vec2(m_windowConfig.width/2, m_windowConfig.height/2), Vec2(m_playerConfig.speed_min, m_playerConfig.speed_max), 0.0f);

		// Player entity's shape, color, and outline thickness are from the configuration file
		entity->cShape = std::make_shared<CShape>(m_playerConfig.shape_radius, m_playerConfig.vertices_max, sf::Color(m_playerConfig.fill_color.color_R, m_playerConfig.fill_color.color_G, m_playerConfig.fill_color.color_B), sf::Color(m_playerConfig.outline_color.color_R, m_playerConfig.outline_color.color_G, m_playerConfig.outline_color.color_B), m_playerConfig.outline_thickness);

		// Player entity's bounding box
		auto bounds = entity->cShape->circle.getGlobalBounds();
		entity->cCollision = std::make_shared<CCollision>(bounds);

		// Input component for the player entity to store user input
		entity->cInput = std::make_shared<CInput>();

		// Player entity in the game class
		m_player = entity;
	}

	// Spawn enemy at a random location in the window
	void Game::spawnEnemy() 
	{
		// TODO: Make sure the enemy is spawned properly with config specs & spawned in window bounds

		// Create enemy entity
		auto entity = m_entities.addEntity(m_enemyConfig.entity_type);

		// Enemy entity's spawning position based on window size
		int ex = rand() % m_window.getSize().x; // rand() % used to randomize the spawning positions
		int ey = rand() % m_window.getSize().y;

		int speedX = (rand() % static_cast<int>((m_enemyConfig.speed_max - m_enemyConfig.speed_min + 1.0) + m_enemyConfig.speed_min));
		int speedY = (rand() % static_cast<int>((m_enemyConfig.speed_max - m_enemyConfig.speed_min + 1.0) + m_enemyConfig.speed_min));

		if (speedX / 2 == 1)
			speedX *= -1;
		if (speedY / 2 == 1)
			speedY *= -1;

		float angle = (rand() % (360 - 0 + 1) + 0);
		entity->cTransform = std::make_shared<CTransform>(Vec2(ex, ey), Vec2(speedX, speedY), angle);

		// Enemy entity's graphics and physics properties from configuration file
		int vertices = (rand() % (m_enemyConfig.vertices_max - m_enemyConfig.vertices_min + 1) + m_enemyConfig.vertices_min);
		entity->cShape = std::make_shared<CShape>(m_enemyConfig.shape_radius, vertices, sf::Color(0, 0, 0), sf::Color(m_enemyConfig.outline_color.color_R, m_enemyConfig.outline_color.color_G, m_enemyConfig.outline_color.color_B), m_enemyConfig.outline_thickness);

		// Enemy entity's bounding box
		auto bounds = entity->cShape->circle.getGlobalBounds();
		entity->cCollision = std::make_shared<CCollision>(bounds);

		// Enemy entity's lifespan
		entity->cLifespan = std::make_shared<CLifespan>(m_enemyConfig.spawn_life);

		// Record of the frame this enemy entity was spawned
		m_lastEnemySpawnTime = m_currentFrame;
	}

	/*
	// Spawns the small enemies after the larger entity collides with a bullet
	void Game::spawnSmallEnemies(std::shared_ptr<Entity> e) {

		// TODO: Spawn small enemies at the locaton of original entity's position
		// 		- Number of small enemies depends on the original entity's vertices
		// 		- Color should be the same as the original entity, but half the size
		// 		- Award double the amount of points if a smaller enemy collides with a bullet

	}
	*/

	// Spawn a bullet from the player entity's to a target location
	void Game::spawnBullet(const std::shared_ptr<Entity>& entity, const Vec2<int>& mousePos) 
	{
		auto bullet = m_entities.addEntity(m_bulletConfig.entity_type);

		float angle = atan2(mousePos.y - entity->cTransform->pos.y, mousePos.x - entity->cTransform->pos.x);

		bullet->cTransform = std::make_shared<CTransform>(Vec2(entity->cTransform->pos.x, entity->cTransform->pos.y), Vec2(static_cast<int>(m_bulletConfig.speed_min * cos(angle)), static_cast<int>(m_bulletConfig.speed_max *sin(angle))), angle);
		
		// Bullet entity properties from the configuration file
		bullet->cShape = std::make_shared<CShape>(m_bulletConfig.shape_radius, m_bulletConfig.vertices_max, sf::Color(m_bulletConfig.fill_color.color_R, m_bulletConfig.fill_color.color_G, m_bulletConfig.fill_color.color_B), sf::Color(m_bulletConfig.outline_color.color_R, m_bulletConfig.outline_color.color_G, m_bulletConfig.outline_color.color_B), m_bulletConfig.outline_thickness);

		// Bullet entity's bounding box
		auto bounds = bullet->cShape->circle.getGlobalBounds();
		bullet->cCollision = std::make_shared<CCollision>(bounds);
	}

	/*
	void Game::spawnSpecialWeapon(std::shared_ptr<Entity> entity) {
		// TODO: Create a special weapon
	}
	*/

	// Implement all lifespan functionality
	void Game::sLifespan() 
	{
		// TODO: Ensure for all entities
		// 		 - if it has lifespan and is alive, scale its alpha channel properly
		for (const auto& e : m_entities.getEntities()) 
		{
			if (e->cLifespan) 
			{
				if (e->cLifespan->remaining > 0)
				{
					e->cLifespan->remaining -= 1;
				}
				else if (e->cLifespan->remaining == 0) 
				{
					e->destroy();
				}
			}
		} // End for loop
	}

	/*
	// Implement all collisions between entities
	void Game::sCollision()
	{
		for (const auto& e : m_entities.getEntities())
		{
			e->cCollision->boundingBox = e->cShape->circle.getGlobalBounds();
		}
		
		for (const auto& b : m_entities.getEntities("bullet"))
		{
			for (const auto& e : m_entities.getEntities("enemy"))
			{
				if (b->cCollision->boundingBox.intersects(e->cCollision->boundingBox))
				{
					e->destroy();
					b->destroy();
					m_score += 5;
				}
			} // End for loop
		} // End for loop
	}
		*/

	// Spawn enemy by time lapse between last spawn and current frame
	void Game::sEnemySpawner()
	{
		if (m_currentFrame - m_lastEnemySpawnTime >= 10)
		{
			spawnEnemy();
		}
	}

	// Render all entities window
	void Game::sRender()
	{	
		m_window.clear();
		m_window.draw(m_sceneBackgroundSprite);
		for (const auto& e : m_entities.getEntities())
		{
			// Position of shape is based on the entity's transform->pos
			e->cShape->circle.setPosition(e->cTransform->pos.x, e->cTransform->pos.y);

			// Rotation of shape is based on the entity's transform->angle
			e->cTransform->angle += 1.0f;
			e->cShape->circle.setRotation(e->cTransform->angle);

			// Draw the entity
			m_window.draw(e->cShape->circle);
		}

		m_text.setString(m_textConfig.text + std::to_string(m_score));

		m_window.draw(m_player->cShape->circle);
		m_window.draw(m_text);
		m_window.display();
	}
} // End namespace