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
		WindowConfig windowConfig;
		FontConfig fontConfig;
		TextConfig textConfig;
		EntityConfig playerConfig;
		EntityConfig enemyConfig;
		EntityConfig bulletConfig;
		TerrainConfig terrainConfig;

		configObject() = default;

		configObject(const WindowConfig wC, const FontConfig fC, const TextConfig txC, const EntityConfig eC1, 
					const EntityConfig eC2, const EntityConfig eC3, const TerrainConfig tC) : windowConfig(wC), fontConfig(fC),
					textConfig(txC), playerConfig(eC1), enemyConfig(eC2), bulletConfig(eC3), terrainConfig(tC)
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