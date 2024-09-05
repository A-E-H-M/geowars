#pragma once

#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>

#include "entity.h"
#include "entity_manager.h"

// Configuration containers
struct WindowConfig { std::string T; int W, H, FR, UNK; };
struct FontConfig { std::string T, F; int S, R, G, B; };
struct PlayerConfig { std::string T; int SR, CR, FR, FG, FB, OR, OG, OB, OT, V; float S; };
struct EnemyConfig { std::string T; int SR, CR, OR, OG, OB, OT, VMIN, VMAX, L, SI; float SMIN, SMAX; };
struct BulletConfig { std::string T; int SR, CR, FR, FG, FB, OR, OG, OB, OT, V, L; float S; };

class Game
{
	private:
		
		// Initalize window, font, and text for score
		sf::RenderWindow m_window;
		sf::Font m_font;
		sf::Text m_text;
		
		// Configuration specs for window and entities
		WindowConfig m_windowConfig;
		FontConfig m_fontConfig;
		PlayerConfig m_playerConfig;
		EnemyConfig m_enemyConfig;
		BulletConfig m_bulletConfig;
		
		// Game state properties
		int m_score = 0;
		int m_currentFrame = 0;
		int m_lastEnemySpawnTime = 0;
		bool m_paused = false;
		bool m_running = true;

		// Initial entity manager and player
		EntityManager m_entities;
		std::shared_ptr<Entity> m_player;

		// Update game state
		void init(const std::string & config);
		void setPaused(); 
		void spawnPlayer();
		void spawnEnemy();
		void spawnBullet(std::shared_ptr<Entity> entity, const Vec2 & mousePos);
		// TODO: Finish the following
		// void spawnSpecialWeapon(std::shared_ptr<Entity> entity);
		// void spawnSmallEnemies(std::shared_ptr<Entity> entity);

		// Sytem updates
		void sMovement();
		void sUserInput();
		void sLifespan();
		void sRender();
		void sEnemySpawner();
		void sCollision();

	public:

		// Initialize and run game
		Game(const std::string & config);
		void run();

};
