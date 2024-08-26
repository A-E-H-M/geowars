#include "../include/geowars/game.h"

#include <iostream>
#include <fstream>
#include <memory>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

Game::Game(const std::string & config)
{
	init(config);
}

void Game::init(const std::string & path)
{
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

void Game::run()
{
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
			// you need to fill in the rest
		}

		sUserInput();
		sRender();

		// increment the current frame
		// may need to be moved when pause implemented
		m_currentFrame++;
	} // End main while loop
}

//void Game::setPaused(bool paused)
void Game::setPaused()
{
	if (m_paused){
		m_paused = false;
	}
	else {
		m_paused = true;
	}
}

void Game::spawnPlayer()
{
	// Create player entity
	auto entity = m_entities.addEntity("player");

	// Variables store the player entity's spawning position based on window size
	float mx = m_window.getSize().x / 2.0f;
	float my = m_window.getSize().y / 2.0f;
	
	// Set the player entity's spawning position, speed, and rotation direction from the configuration file
	entity->cTransform = std::make_shared<CTransform>(Vec2(m_windowConfig.W/2, m_windowConfig.H/2), Vec2(m_playerConfig.S, m_playerConfig.S), 0.0f);

	// Set the player entity's shape, color, and outline thickness from the configuration file
	entity->cShape = std::make_shared<CShape>(m_playerConfig.SR, m_playerConfig.V, sf::Color(m_playerConfig.FR, m_playerConfig.FG, m_playerConfig.FB), sf::Color(m_playerConfig.OR, m_playerConfig.OG, m_playerConfig.OB), m_playerConfig.OT);

	// Set the player entity's bounding box
	auto bounds = entity->cShape->circle.getGlobalBounds();
	entity->cCollision = std::make_shared<CCollision>(bounds);

	// Add an input component to the player entity to store user input
	entity->cInput = std::make_shared<CInput>();

	// Assign the entity to the m_player variable in the game class
	m_player = entity;
}

void Game::spawnEnemy()
{
	// TODO: make sure the enemy is spawned properly with the m_enemyConfig variables
	// 		 the enemy must be spawned completely within the bounds of the window
	// 		 you will have to read from the config file and not hard code variables 
	// Create enemy entity
	auto entity = m_entities.addEntity("enemy");

	// Variables to store the enemy entity's spawning position based on window size
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

	// The entity's shape will have radius 32, 8 sides, dark grey fill, and red outline of thickness 4
	int vertices = (rand() % (m_enemyConfig.VMAX - m_enemyConfig.VMIN + 1) + m_enemyConfig.VMIN);
	entity->cShape = std::make_shared<CShape>(m_enemyConfig.SR, vertices, sf::Color(0, 0, 0), sf::Color(m_enemyConfig.OR, m_enemyConfig.OG, m_enemyConfig.OB), m_enemyConfig.OT);

	// setting bounding box
	auto bounds = entity->cShape->circle.getGlobalBounds();
	entity->cCollision = std::make_shared<CCollision>(bounds);

	// initiate lifespan
	entity->cLifespan = std::make_shared<CLifespan>(m_enemyConfig.L);

	// record when the most recent enemy was spawned
	m_lastEnemySpawnTime = m_currentFrame;
}

/*
// spawns the small enemies when a big one (input entity e) explodes
void Game::spawnSmallEnemies(std::shared_ptr<Entity> e)
{
	// TODO: spawn small enemies at the locaton of the input enemy e

	// when we create the smaller enemy, we have to read the values of the original enemy
	//  - spawn a number of small enemies equal to the vertices of the original enemy
	//  - set each small enemy to the same color as the original, half the size
	//  - small enemies are worth double points of the original enemy

}
*/

// spawns a bullet from a given entity to a target location
void Game::spawnBullet(std::shared_ptr<Entity> entity, const Vec2 & mousePos)
{
	// TODO: implement the spawning of a bullet which travels toward target
	// 		 - bullet speed is given as a scalar speed
	// 		 - you must set the velocity by using the formula in notes
	
	auto bullet = m_entities.addEntity("bullet");

	// Bullet speed is given as a scalar speed
	bullet->cTransform = std::make_shared<CTransform>(Vec2(entity->cTransform->pos.x, entity->cTransform->pos.y), Vec2(m_bulletConfig.S, m_bulletConfig.S), 0);
	
	// Setting bullet attributes
	bullet->cShape = std::make_shared<CShape>(m_bulletConfig.SR, m_bulletConfig.V, sf::Color(m_bulletConfig.FR, m_bulletConfig.FG, m_bulletConfig.FB), sf::Color(m_bulletConfig.OR, m_bulletConfig.OG, m_bulletConfig.OB), m_bulletConfig.OT);

	// Setting bounding box
	auto bounds = bullet->cShape->circle.getGlobalBounds();
	bullet->cCollision = std::make_shared<CCollision>(bounds);

}

/*
void Game::spawnSpecialWeapon(std::shared_ptr<Entity> entity)
{
	// TODO: implement your own special weapon
}
*/

void Game::sMovement()
{
	// TODO: implement all entity movement in this function
	// 		 you should read the m_player->cInput component to determine if the player is moving

	// Movement speed update
	for (auto& e : m_entities.getEntities()){
		e->cTransform->pos.x += e->cTransform->velocity.x;
		e->cTransform->pos.y += e->cTransform->velocity.y;
		}

	m_player->cTransform->velocity = { 0, 0 };

	// implement player movement
	if (m_player->cInput->up){
		m_player->cTransform->velocity.y = m_playerConfig.S * -1;
	}
	if (m_player->cInput->down){
		m_player->cTransform->velocity.y = m_playerConfig.S;
	}
	if (m_player->cInput->left){
		m_player->cTransform->velocity.x = m_playerConfig.S * -1;
	}
	if (m_player->cInput->right){
	m_player->cTransform->velocity.x = m_playerConfig.S;
	}
}

void Game::sLifespan()
{
	// TODO: implement all lifespan functionality
	//
	// 	for all entities
	// 		 if entity has no lifespan component, skip it
	// 		 if entity has > 0 remaining lifespan, subtract 1
	// 		 if it has lifespan and is alive
	// 		 	scale its alpha channel properly
	// 		 if it has lifespan and its time is up
	// 		 	destroy the entity
	for (auto e: m_entities.getEntities()){
		if (e->cLifespan){
			if (e->cLifespan->remaining > 0){
				e->cLifespan->remaining -= 1;
			}
			else if (e->cLifespan->remaining == 0){
				e->destroy();
			}
		}
	}
	
}

void Game::sCollision()
{
	// TODO: implement all proper collisions between entities
	// 		 be sure to use the collision radius, NOT the shape radius

	for (auto e : m_entities.getEntities()){
		e->cCollision->boundingBox = e->cShape->circle.getGlobalBounds();
	}
	
	for (auto b : m_entities.getEntities("bullet"))
	{
		for (auto e : m_entities.getEntities("enemy"))
		{
			if (b->cCollision->boundingBox.intersects(e->cCollision->boundingBox)){
				e->destroy();
				b->destroy();
			}
		}
	}

}

void Game::sEnemySpawner()
{
	if (m_currentFrame - m_lastEnemySpawnTime >= 10){
		spawnEnemy();
	}
}

void Game::sRender()
{
	// TODO: change the code below to draw ALL of the entities
	// 		 sample drawing of the player Entity that we have created
	m_window.clear();
	for (auto& e : m_entities.getEntities())
	{
		// set the position of the shape based on the entity's transform->pos
		e->cShape->circle.setPosition(e->cTransform->pos.x, e->cTransform->pos.y);

		// set the rotation of the shape based on the entity's transform->angle
		e->cTransform->angle += 1.0f;
		e->cShape->circle.setRotation(e->cTransform->angle);

		// draw the entity's sf::CircleShape
		m_window.draw(e->cShape->circle);
	}
	m_window.draw(m_player->cShape->circle);
	m_window.draw(m_text);
	m_window.display();
}

void Game::sUserInput()
{
	// TODO: handle user input here
	// 		 note that you shold only be setting the player's input component variables here
	// 		 you should not implement the player's movement logic here
	// 		 the movement system will read the variables you set in this function
	
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		// this event triggers when the window is closed
		if (event.type == sf::Event::Closed)
		{
			m_running = false;
		}
		
		// this event is triggered when a key is pressed
		if (event.type == sf::Event::KeyPressed)
		{
			switch (event.key.code)
			{
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
	
		// this event is triggered when a key is released
		if (event.type == sf::Event::KeyReleased)
		{
			switch (event.key.code)
			{
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
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				std::cout << "Left Mouse Button Clicked at (" << event.mouseButton.x << ", " << event.mouseButton.y << ")/n";
				// call spawnBullet here
				spawnBullet(m_player, Vec2(event.mouseButton.x, event.mouseButton.y));

			}

			if (event.mouseButton.button == sf::Mouse::Right)
			{
				std::cout << "Right Mouse Button Clicked at (" << event.mouseButton.x << ", " << event.mouseButton.y << ")/n";
				// call spawnSpecialWeapon here
			}
		}
	}
}
