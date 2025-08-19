#pragma once

#include <string>
#include <string_view>
#include <nlohmann/json.hpp>

#include "geowars/config_components.hpp"

namespace GWars 
{
	struct configObject
	{
		// Configuration specs for window, text strings, and entities
		WindowConfig windowConfig_1;

		FontConfig fontConfig_1;
		FontConfig fontConfig_2;

		TextConfig textConfig_1;
		TextConfig textConfig_2;
		TextConfig textConfig_3;

		TextureConfig textureConfig_1;
		TextureConfig textureConfig_2;
		TextureConfig textureConfig_3;

		EntityConfig entityConfig_1;
		EntityConfig entityConfig_2;
		EntityConfig entityConfig_3;

		TerrainConfig terrainConfig_1;

		configObject(){};

		configObject(const WindowConfig wC_1, const FontConfig fC_1, const FontConfig fC_2,
					const TextConfig txC_1, const TextConfig txC_2, const TextConfig txC_3,
					const TextureConfig tC_1, const TextureConfig tC_2, const TextureConfig tC_3,
					const EntityConfig eC_1, const EntityConfig eC_2, const EntityConfig eC_3, 
					const TerrainConfig tnC_1) 
					: windowConfig_1(wC_1), fontConfig_1(fC_1), fontConfig_2(fC_2), 
					textConfig_1(txC_1), textConfig_2(txC_2), textConfig_3(txC_3),
					textureConfig_1(tC_1), textureConfig_2(tC_2), textureConfig_3(tC_3),
					entityConfig_1(eC_1), entityConfig_2(eC_2), entityConfig_3(eC_3), 
					terrainConfig_1(tnC_1)
					{};
	};

	struct GameConfig
	{
		const std::string configFileName;

		nlohmann::json configParse();
		configObject configInit();
		
		GameConfig(std::string_view configFile) : configFileName (configFile) {};
	};

} // End namespace