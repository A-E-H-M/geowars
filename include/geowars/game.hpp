#pragma once

#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>

#include "geowars/entity.hpp"
#include "geowars/entity_manager.hpp"
#include "geowars/terrain.hpp"

namespace GWars
{

	// Window configuration properties (Width, Height, Frame Rate, Unknown)
	struct WindowConfig { int W, H, FR, UNK; };

	// Font configuration properties (File path, Size, RGB color values)
	struct FontConfig { std::string F; int S, R, G, B; };

	// Entity configuration properties (Type, Shape Radius, Collision Radius, Speed Min/Max, Fill RGB, Outline RGB, Outline Thickness, Vertices Min/Max, Spawn Life, Spawn Interval)
	struct EntityConfig { std::string T; int SR, CR, SMin, SMax, FR, FG, FB, OR, OG, OB, OT, VMin, VMax, SL, SI; };

	// Terrain configuration properties (File path, Name, Difficulty)
	struct TerrainConfig { std::string F, N; int D; };

	// Text configuration properties (Window Title, Score Text)
	struct TextConfig { std::string WT, ST; };

	class Game
	{
		using json = nlohmann::json;

		private:
			
			// Initialize window, font, and text for score
			sf::RenderWindow m_window;
			sf::Font m_font;
			sf::Text m_text;

			// Initialize textures
			sf::Texture m_terrain;
			sf::Sprite m_sceneBackgroundSprite;

			// Configuration specs for window, text strings, and entities
			WindowConfig m_windowConfig;
			FontConfig m_fontConfig;
			EntityConfig m_playerConfig;
			EntityConfig m_enemyConfig;
			EntityConfig m_bulletConfig;
			TerrainConfig m_terrainConfig;
			TextConfig m_textConfig;
			
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
			void init(const json& game_config);
			void setPaused(); 
			void spawnPlayer();
			void spawnEnemy();
			void spawnBullet(const std::shared_ptr<Entity>& entity, const Vec2<int>& mousePos);
			// TODO: Finish the following
			// void spawnSpecialWeapon(std::shared_ptr<Entity> entity);
			// void spawnSmallEnemies(std::shared_ptr<Entity> entity);

			// System updates
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
}; // End namespace
