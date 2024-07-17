#pragma once

#include <iostream>
#include <string>

#include "entity.h"
#include "entity_manager.h"

#include <SFML/Graphics.hpp>

// Custom struct for saving window variables from config
struct WindowConfig { std::string T; int W, H, FR, UNK; };
struct FontConfig { std::string T, F; int S, R, G, B; };
struct PlayerConfig	{ std::string T; int SR, CR, FR, FG, FB, OR, OG, OB, OT, V; float S; };
struct EnemyConfig	{ std::string T; int SR, CR, OR, OG, OB, OT, VMIN, VMAX, L, SI; float SMIN, SMAX; };
struct BulletConfig	{ std::string T; int SR, CR, FR, FG, FB, OR, OG, OB, OT, V, L; float S; };

class Game
{
	sf::RenderWindow	m_window; 					// the window we will draw to
	EntityManager		m_entities;					// vector of entities to maintain
	sf::Font			m_font;						// the font we will use to draw
	sf::Text			m_text;						// the score text to be drawn to the screen
	WindowConfig		m_windowConfig;				// Custom struct for accessing window variables
	FontConfig			m_fontConfig;
	PlayerConfig		m_playerConfig;
	EnemyConfig			m_enemyConfig;
	BulletConfig		m_bulletConfig;
	int					m_score = 0;
	int					m_currentFrame = 0;
	int					m_lastEnemySpawnTime = 0;
	bool				m_paused = false;			// whether we update game logic
	bool				m_running = true;			// whether the game is running
	
	std::shared_ptr<Entity> m_player;

	void init(const std::string & config);			// initialize the GameState with a config file path
	void setPaused(bool paused);					// pause the game
	
	// Initial entity spawns
	void spawnPlayer();
	void spawnEnemy();
	//void spawnSmallEnemies(std::shared_ptr<Entity> entity);
	void spawnBullet(std::shared_ptr<Entity> entity, const Vec2 & mousePos);
	//void spawnSpecialWeapon(std::shared_ptr<Entity> entity);
	
	// Sytem updates
	void sMovement();								// System: Entity position / movement update
	void sUserInput();								// System: User input
	void sLifespan();								// System: Lifespan
	void sRender();									// System: Render / drawing
	void sEnemySpawner();							// System: Spawns Enemies
	void sCollision();								// System: Collisions

public:
	Game(const std::string & config);				// constructor, takes in game config
	
	void run();
};
