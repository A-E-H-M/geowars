#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "geowars/entity.hpp"
#include "geowars/entity_manager.hpp"
#include "geowars/terrain.hpp"
#include "geowars/config_components.hpp"
#include "geowars/config.hpp"
#include "geowars/window_manager.hpp"
#include "geowars/input.hpp"
#include "geowars/movement.hpp"
#include "geowars/collisions.hpp"

namespace GWars
{
	class Game
	{
		private:
			// Window manager
			friend class Window_Manager;
			Window_Manager m_window_manager;

			// Window elements
			sf::RenderWindow m_window;
			sf::Font m_font;
			sf::Text m_text;

			// Assets
			sf::Texture m_terrain;
			sf::Sprite m_sceneBackgroundSprite;

			// Object configurations
			WindowConfig m_windowConfig;
			FontConfig m_fontConfig;
			TextConfig m_textConfig;
			EntityConfig m_playerConfig;
			EntityConfig m_enemyConfig;
			EntityConfig m_bulletConfig;
			TerrainConfig m_terrainConfig;

			// Input
			friend class Input;
			Input m_input;

			//Mechanics
			friend class Movement;
			Movement m_movement;

			friend class Collisions;
			Collisions m_collisions;
			
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
			void init(const configObject& gameConfig);
			void setPaused() { m_paused = !m_paused; }
			void spawnPlayer();
			void spawnEnemy();
			void spawnBullet(const std::shared_ptr<Entity>& entity, const Vec2<int>& mousePos);
			// TODO: Finish the following
			// void spawnSpecialWeapon(std::shared_ptr<Entity> entity);
			// void spawnSmallEnemies(std::shared_ptr<Entity> entity);

			// System updates
			void sLifespan();
			void sRender();
			void sEnemySpawner();
			//void sCollision();

		public:

			// Initialize and run game
			Game(const configObject& gameConfig);
			void run();
	};
} // End namespace
