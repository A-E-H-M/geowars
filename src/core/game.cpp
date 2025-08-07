#include <iostream>
#include <fstream>
#include <memory>
#include <cmath>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <nlohmann/json.hpp>

#include "geowars/game.hpp"

using json = nlohmann::json;
namespace GWars
{
	Game::Game(const std::string& config)
	{
		init(game_config);
	}

	void Game::init(const json& game_config)
	{	
		// Spawn the player
		spawnPlayer();
	}

	void Game::run() {
		
		// Render start window
		m_window.create(sf::VideoMode(m_windowConfig.W, m_windowConfig.H), m_textConfig.WT);
		m_window.setFramerateLimit(m_windowConfig.FR);

		// Set up score text
		m_text.setFont(m_font);
		m_text.setString(m_textConfig.ST + std::to_string(0));
		m_text.setPosition(10, m_windowConfig.H - static_cast<float>(m_text.getCharacterSize()) - 10);

		// Load textures
		m_terrain.loadFromFile(m_terrainConfig.F);
		Terrain m_sceneBackground(m_terrainConfig.D, m_terrainConfig.N, m_terrain);
		m_sceneBackgroundSprite.setTexture(m_terrain);

		// Main while loop
		while (m_running)
		{
			m_entities.update();

			if (!m_paused)
			{
				sEnemySpawner();
				sLifespan();
				sMovement();
				sCollision();
			}

			sUserInput();
			sRender();

			m_currentFrame++;
		} // End main while loop

	}

	// Pause the game
	void Game::setPaused() 
	{
		if (m_paused)
		{
			m_paused = false;
		}

		else 
		{
			m_paused = true;
		}

	}

	// Spawn player entity at the center of the window
	void Game::spawnPlayer() 
	{	
		// Create player entity
		auto entity = m_entities.addEntity(m_playerConfig.T);

		// Player entity's spawning position based on window size
		//float mx = m_window.getSize().x / 2.0f;
		//float my = m_window.getSize().y / 2.0f;
		
		// Player entity's spawning position, speed, and rotation direction are from the configuration file
		entity->cTransform = std::make_shared<CTransform>(Vec2(m_windowConfig.W/2, m_windowConfig.H/2), Vec2(m_playerConfig.SMin, m_playerConfig.SMax), 0.0f);

		// Player entity's shape, color, and outline thickness are from the configuration file
		entity->cShape = std::make_shared<CShape>(m_playerConfig.SR, m_playerConfig.VMax, sf::Color(m_playerConfig.FR, m_playerConfig.FG, m_playerConfig.FB), sf::Color(m_playerConfig.OR, m_playerConfig.OG, m_playerConfig.OB), m_playerConfig.OT);

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
		auto entity = m_entities.addEntity(m_enemyConfig.T);

		// Enemy entity's spawning position based on window size
		int ex = rand() % m_window.getSize().x; // rand() % used to randomize the spawning positions
		int ey = rand() % m_window.getSize().y;

		int speedX = (rand() % static_cast<int>((m_enemyConfig.SMax - m_enemyConfig.SMin + 1.0) + m_enemyConfig.SMin));
		int speedY = (rand() % static_cast<int>((m_enemyConfig.SMax - m_enemyConfig.SMin + 1.0) + m_enemyConfig.SMin));

		if (speedX / 2 == 1)
			speedX *= -1;
		if (speedY / 2 == 1)
			speedY *= -1;

		float angle = (rand() % (360 - 0 + 1) + 0);
		entity->cTransform = std::make_shared<CTransform>(Vec2(ex, ey), Vec2(speedX, speedY), angle);

		// Enemy entity's graphics and physics properties from configuration file
		int vertices = (rand() % (m_enemyConfig.VMax - m_enemyConfig.VMin + 1) + m_enemyConfig.VMin);
		entity->cShape = std::make_shared<CShape>(m_enemyConfig.SR, vertices, sf::Color(0, 0, 0), sf::Color(m_enemyConfig.OR, m_enemyConfig.OG, m_enemyConfig.OB), m_enemyConfig.OT);

		// Enemy entity's bounding box
		auto bounds = entity->cShape->circle.getGlobalBounds();
		entity->cCollision = std::make_shared<CCollision>(bounds);

		// Enemy entity's lifespan
		entity->cLifespan = std::make_shared<CLifespan>(m_enemyConfig.SL);

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
		auto bullet = m_entities.addEntity(m_bulletConfig.T);

		float angle = atan2(mousePos.y - entity->cTransform->pos.y, mousePos.x - entity->cTransform->pos.x);

		bullet->cTransform = std::make_shared<CTransform>(Vec2(entity->cTransform->pos.x, entity->cTransform->pos.y), Vec2(static_cast<int>(m_bulletConfig.SMin * cos(angle)), static_cast<int>(m_bulletConfig.SMax *sin(angle))), angle);
		
		// Bullet entity properties from the configuration file
		bullet->cShape = std::make_shared<CShape>(m_bulletConfig.SR, m_bulletConfig.VMax, sf::Color(m_bulletConfig.FR, m_bulletConfig.FG, m_bulletConfig.FB), sf::Color(m_bulletConfig.OR, m_bulletConfig.OG, m_bulletConfig.OB), m_bulletConfig.OT);

		// Bullet entity's bounding box
		auto bounds = bullet->cShape->circle.getGlobalBounds();
		bullet->cCollision = std::make_shared<CCollision>(bounds);
	}

	/*
	void Game::spawnSpecialWeapon(std::shared_ptr<Entity> entity) {
		// TODO: Create a special weapon
	}
	*/

	// Implement all entity's movements
	void Game::sMovement() 
	{
		// Movement speed update
		for (auto& e : m_entities.getEntities()){
			e->cTransform->pos.x += e->cTransform->velocity.x;
			e->cTransform->pos.y += e->cTransform->velocity.y;
			}

		m_player->cTransform->velocity = { 0, 0 };

		// Implement player movement
		if (m_player->cInput->up) {
			m_player->cTransform->velocity.y = m_playerConfig.SMax * -1;
		}
		if (m_player->cInput->down) {
			m_player->cTransform->velocity.y = m_playerConfig.SMax;
		}
		if (m_player->cInput->left) {
			m_player->cTransform->velocity.x = m_playerConfig.SMax * -1;
		}
		if (m_player->cInput->right) {
		m_player->cTransform->velocity.x = m_playerConfig.SMax;
		}
	}

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

		m_text.setString(m_textConfig.ST + std::to_string(m_score));

		m_window.draw(m_player->cShape->circle);
		m_window.draw(m_text);
		m_window.display();
	}

	// Assess for user input
	void Game::sUserInput() 
	{	
		sf::Event event;

		while (m_window.pollEvent(event))
		{
			// Event triggers the window to closed
			if (event.type == sf::Event::Closed)
			{
				m_running = false;
			}
			
			// Event is triggered when a key is pressed
			if (event.type == sf::Event::KeyPressed)
			{
				switch (event.key.code)
				{
					case sf::Keyboard::W:
						m_player->cInput->up = true;
						break;
					case sf::Keyboard::S:
						m_player->cInput->down = true;
						break;
					case sf::Keyboard::A:
						m_player->cInput->left = true;
						break;
					case sf::Keyboard::D:
						m_player->cInput->right = true;
						break;
					case sf::Keyboard::Space:
						setPaused();
						break;
					case sf::Keyboard::Escape:
						m_running = false;
						break;
					default: break;
				}
			}
		
			// Event is triggered when a key is released
			if (event.type == sf::Event::KeyReleased)
			{
				switch (event.key.code)
				{
					case sf::Keyboard::W:
						m_player->cInput->up = false;
						break;
					case sf::Keyboard::S:
						m_player->cInput->down = false;
						break;
					case sf::Keyboard::A:
						m_player->cInput->left = false;
						break;
					case sf::Keyboard::D:
						m_player->cInput->right = false;
						break;
					default: break;
				}
			}

			// Event is triggered when a mouse key is pressed
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					spawnBullet(m_player, Vec2(event.mouseButton.x, event.mouseButton.y));
				}

				if (event.mouseButton.button == sf::Mouse::Right)
				{
					// TODO: Spawn special weapon here
				}
			}
		} // End while loop
	}
}; // End namespace