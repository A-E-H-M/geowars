#include "../include/geowars/game.hpp"

#include <iostream>
#include <fstream>
#include <memory>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

Game::Game(const std::string & config) {
	
	init(config);

}

void Game::init(const std::string & path) {

	// Read & store configuration file variables, then close file
	std::fstream file(path);
	if (file.is_open()) {
		file >> m_windowConfig.T >> m_windowConfig.W >> m_windowConfig.H >> m_windowConfig.FR >> m_windowConfig.UNK;
		
		file >> m_fontConfig.T >> m_fontConfig.F >> m_fontConfig.S >> m_fontConfig.R >> m_fontConfig.G >> m_fontConfig.B;
		
		file >> m_playerConfig.T >> m_playerConfig.SR >> m_playerConfig.CR >> m_playerConfig.S >> m_playerConfig.FR >> m_playerConfig.FG >> m_playerConfig.FB >> m_playerConfig.OR >> m_playerConfig.OG >> m_playerConfig.OB >> m_playerConfig.OT >> m_playerConfig.V;
		
		file >> m_enemyConfig.T >> m_enemyConfig.SR >> m_enemyConfig.CR >> m_enemyConfig.SMIN >> m_enemyConfig.SMAX >> m_enemyConfig.OR >> m_enemyConfig.OG >> m_enemyConfig.OB >> m_enemyConfig.OT >> m_enemyConfig.VMIN >> m_enemyConfig.VMAX >> m_enemyConfig.L >> m_enemyConfig.SI;
		
		file >> m_bulletConfig.T >> m_bulletConfig.SR >> m_bulletConfig.CR >> m_bulletConfig.S  >> m_bulletConfig.FR >> m_bulletConfig.FG >> m_bulletConfig.FB >> m_bulletConfig.OR >> m_bulletConfig.OG >> m_bulletConfig.OB >> m_bulletConfig.OT >> m_bulletConfig.V >> m_bulletConfig.L;
	}
	else {
		std::cerr << "Couldn't open config file for reading. \n";
	}
	file.close();

	// Load and verify font
	if (!m_font.loadFromFile(m_fontConfig.F)){
		std::cerr << "Could not load font!\n";
		exit(-1);
	}

	spawnPlayer();

}

void Game::run() {
	
	// Render start window
	m_window.create(sf::VideoMode(m_windowConfig.W, m_windowConfig.H), "Best Game Ever");
	m_window.setFramerateLimit(m_windowConfig.FR);

	// Set up score text
	m_text.setFont(m_font);
	m_text.setString("Your Score, Baby: ");
	m_text.setPosition(10, m_windowConfig.H - (float)m_text.getCharacterSize() - 10);

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

//void Game::setPaused(bool paused)
void Game::setPaused() {

	if (m_paused){
		m_paused = false;
	}
	else {
		m_paused = true;
	}

}

// Spawn player entity at the center of the window
void Game::spawnPlayer() {
	
	// Create player entity
	auto entity = m_entities.addEntity("player");

	// Player entity's spawning position based on window size
	float mx = m_window.getSize().x / 2.0f;
	float my = m_window.getSize().y / 2.0f;
	
	// Player entity's spawning position, speed, and rotation direction are from the configuration file
	entity->cTransform = std::make_shared<CTransform>(Vec2(m_windowConfig.W/2, m_windowConfig.H/2), Vec2(m_playerConfig.S, m_playerConfig.S), 0.0f);

	// Player entity's shape, color, and outline thickness are from the configuration file
	entity->cShape = std::make_shared<CShape>(m_playerConfig.SR, m_playerConfig.V, sf::Color(m_playerConfig.FR, m_playerConfig.FG, m_playerConfig.FB), sf::Color(m_playerConfig.OR, m_playerConfig.OG, m_playerConfig.OB), m_playerConfig.OT);

	// Player entity's bounding box
	auto bounds = entity->cShape->circle.getGlobalBounds();
	entity->cCollision = std::make_shared<CCollision>(bounds);

	// Input component for the player entity to store user input
	entity->cInput = std::make_shared<CInput>();

	// Player entity in the game class
	m_player = entity;

}

// Spawn enemy at a random location in the window
void Game::spawnEnemy() {
	// TODO: Make sure the enemy is spawned properly with config specs & spawned in window bounds

	// Create enemy entity
	auto entity = m_entities.addEntity("enemy");

	// Enemy entity's spawning position based on window size
	float ex = rand() % m_window.getSize().x; // rand() % used to randomize the spawning positions
	float ey = rand() % m_window.getSize().y;

	float speedX = (rand() % static_cast<int>((m_enemyConfig.SMAX - m_enemyConfig.SMIN + 1.0) + m_enemyConfig.SMIN));
	float speedY = (rand() % static_cast<int>((m_enemyConfig.SMAX - m_enemyConfig.SMIN + 1.0) + m_enemyConfig.SMIN));

	if (speedX / 2 == 1)
		speedX *= -1;
	if (speedY / 2 == 1)
		speedY *= -1;

	float angle = (rand() % (360 - 0 + 1) + 0);
	entity->cTransform = std::make_shared<CTransform>(Vec2(ex, ey), Vec2(speedX, speedY), angle);

	// Enemy entity's graphics and physics properties from configuration file
	int vertices = (rand() % (m_enemyConfig.VMAX - m_enemyConfig.VMIN + 1) + m_enemyConfig.VMIN);
	entity->cShape = std::make_shared<CShape>(m_enemyConfig.SR, vertices, sf::Color(0, 0, 0), sf::Color(m_enemyConfig.OR, m_enemyConfig.OG, m_enemyConfig.OB), m_enemyConfig.OT);

	// Enemy entity's bounding box
	auto bounds = entity->cShape->circle.getGlobalBounds();
	entity->cCollision = std::make_shared<CCollision>(bounds);

	// Enemy entity's lifespan
	entity->cLifespan = std::make_shared<CLifespan>(m_enemyConfig.L);

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
void Game::spawnBullet(std::shared_ptr<Entity> entity, const Vec2 & mousePos) {
	// TODO: Ensure bullet speed scalar is used & add velocity formula
	
	auto bullet = m_entities.addEntity("bullet");

	// Bullet speed is given as a scalar speed
	bullet->cTransform = std::make_shared<CTransform>(Vec2(entity->cTransform->pos.x, entity->cTransform->pos.y), Vec2(m_bulletConfig.S, m_bulletConfig.S), 0);
	
	// Bullet entity properties from the configuration file
	bullet->cShape = std::make_shared<CShape>(m_bulletConfig.SR, m_bulletConfig.V, sf::Color(m_bulletConfig.FR, m_bulletConfig.FG, m_bulletConfig.FB), sf::Color(m_bulletConfig.OR, m_bulletConfig.OG, m_bulletConfig.OB), m_bulletConfig.OT);

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
void Game::sMovement() {

	// Movement speed update
	for (auto& e : m_entities.getEntities()){
		e->cTransform->pos.x += e->cTransform->velocity.x;
		e->cTransform->pos.y += e->cTransform->velocity.y;
		}

	m_player->cTransform->velocity = { 0, 0 };

	// Implement player movement
	if (m_player->cInput->up) {
		m_player->cTransform->velocity.y = m_playerConfig.S * -1;
	}
	if (m_player->cInput->down) {
		m_player->cTransform->velocity.y = m_playerConfig.S;
	}
	if (m_player->cInput->left) {
		m_player->cTransform->velocity.x = m_playerConfig.S * -1;
	}
	if (m_player->cInput->right) {
	m_player->cTransform->velocity.x = m_playerConfig.S;
	}
}

// Implement all lifespan functionality
void Game::sLifespan() {
	// TODO: Ensure for all entities
	// 		 - if entity has no lifespan component, skip it
	// 		 - if entity has > 0 remaining lifespan, subtract 1
	// 		 - if it has lifespan and is alive, scale its alpha channel properly
	// 		 - if it has lifespan and its time is up destroy the entity
	for (auto e: m_entities.getEntities()) {
		if (e->cLifespan) {
			if (e->cLifespan->remaining > 0) {
				e->cLifespan->remaining -= 1;
			}
			else if (e->cLifespan->remaining == 0) {
				e->destroy();
			}
		}
	}
	
}

// Implement all collisions between entities
void Game::sCollision()
{
	// TODO: Ensure the use of the bounding box, not the shape of the entity
	for (auto e : m_entities.getEntities()){
		e->cCollision->boundingBox = e->cShape->circle.getGlobalBounds();
	}
	
	for (auto b : m_entities.getEntities("bullet")) {
		for (auto e : m_entities.getEntities("enemy")) {
			if (b->cCollision->boundingBox.intersects(e->cCollision->boundingBox)) {
				e->destroy();
				b->destroy();
			}
		}
	}

}

// Spawn enemy by time lapse between last spawn and current frame
void Game::sEnemySpawner() {

	if (m_currentFrame - m_lastEnemySpawnTime >= 10) {
		spawnEnemy();
	}

}

// Render all entities window
void Game::sRender() {
	
	m_window.clear();
	for (auto& e : m_entities.getEntities()) {
		// Position of shape is based on the entity's transform->pos
		e->cShape->circle.setPosition(e->cTransform->pos.x, e->cTransform->pos.y);

		// Rotation of shape is based on the entity's transform->angle
		e->cTransform->angle += 1.0f;
		e->cShape->circle.setRotation(e->cTransform->angle);

		// Draw the entity
		m_window.draw(e->cShape->circle);
	}
	m_window.draw(m_player->cShape->circle);
	m_window.draw(m_text);
	m_window.display();

}

// Assess for user input
void Game::sUserInput() {
	
	sf::Event event;
	while (m_window.pollEvent(event)) {
		// Event triggers the window to closed
		if (event.type == sf::Event::Closed) {
			m_running = false;
		}
		
		// Event is triggered when a key is pressed
		if (event.type == sf::Event::KeyPressed) {
			switch (event.key.code) {
				case sf::Keyboard::W:
					std::cout << "W Key Pressed/n";
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
		if (event.type == sf::Event::KeyReleased) {
			switch (event.key.code) {
				case sf::Keyboard::W:
					std::cout << "W Key Released/n";
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
		if (event.type == sf::Event::MouseButtonPressed) {
			if (event.mouseButton.button == sf::Mouse::Left) {
				std::cout << "Left Mouse Button Clicked at (" << event.mouseButton.x << ", " << event.mouseButton.y << ")/n";
				spawnBullet(m_player, Vec2(event.mouseButton.x, event.mouseButton.y));
			}

			if (event.mouseButton.button == sf::Mouse::Right) {
				std::cout << "Right Mouse Button Clicked at (" << event.mouseButton.x << ", " << event.mouseButton.y << ")/n";
				// TODO: Spawn special weapon here
			}
		}
	}
}
