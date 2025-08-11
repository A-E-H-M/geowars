#pragma once

#include <string>
#include <iostream>
#include <nlohmann/json.hpp>

#include "config_components.hpp"

using json = nlohmann::json;

namespace GWars 
{
	struct configObject
	{
		// Configuration specs for window, text strings, and entities
		WindowConfig m_windowConfig;
		FontConfig m_fontConfig;
		TextConfig m_textConfig;
		EntityConfig m_playerConfig;
		EntityConfig m_enemyConfig;
		EntityConfig m_bulletConfig;
		TerrainConfig m_terrainConfig;

		configObject(const WindowConfig wC, const FontConfig fC, const TextConfig txC, const EntityConfig eC1, 
					const EntityConfig eC2, const EntityConfig eC3, const TerrainConfig tC) : m_windowConfig(wC), m_fontConfig(fC),
					m_textConfig(txC), m_playerConfig(eC1), m_enemyConfig(eC2), m_bulletConfig(eC3), m_terrainConfig(tC)
					{};
	};

	struct GameConfig
	{
		const std::string configFileName;

		json configParse(const std::string& textString);
		configObject configInit();
		
		GameConfig(const std::string& configFile) : configFileName (configFile)
		{};
	};

}; // End namespace