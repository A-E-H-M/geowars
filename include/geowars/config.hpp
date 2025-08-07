#pragma once

#include <string>
#include <nlohmann/json.hpp>

#include "geowars/config_components.hpp"

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

		configObject(const WindowConfig wC, const FontConfig fC, const TextConfig tC, const EntityConfig eC1, 
					const EntityConfig eC2, const EntityConfig eC3, const TerrainConfig tC) : m_windowConfig(wc), m_fontConfig(fC),
					m_playerConfig(eC1), m_enemyConfig(eC2), m_bulletConfig(eC3), m_terrainConfig(tC)
					{};
	};

	class GameConfig
	{
		const std::string configFileName;

		bool configParse(const std::string& textString);
		configObject configInit(const std::string& text);
		
		GameConfig(const std::string& configFile) : configFileName (configFile)
		{};
	};

	json GameConfig::configParse(const std::string& textString)
	{
    	// Verify config file can be located and parsed, if not, print an error message
		try
		{
			std::ifstream f(config);
			//json jObject = json::parse(f);
			return json::parse(f);
        }

		catch (const json::parse_error& e)
		{
			std::cout << "Message: Couldn't open config file for reading. \n"
					<< "Error: " << e.what() << "Exception ID: " << e.id << "\n";
			exit(-1);
			return NULL;
		}
	}

	configObject GameConfig::configInit() 
	{
		json game_config = configParse(configFileName);
		
		WindowConfig t_windowConfig;
		FontConfig t_fontConfig;
		TextConfig t_textConfig;
		EntityConfig t_playerConfig;
		EntityConfig t_enemyConfig;
		EntityConfig t_bulletConfig;
		TerrainConfig t_terrainConfig;

		// Set window configurations
		t_windowConfig.W = game_config["window"]["width"];
		t_windowConfig.H = game_config["window"]["height"];
		t_windowConfig.FR = game_config["window"]["frame_rate"];
		T_windowConfig.UNK = game_config["window"]["fullscreen"];	

		// Set on screen text strings
		t_textConfig.WT = game_config["text"]["window_text"];
		t_textConfig.ST = game_config["text"]["screen_text"];

		// Set font configurations
		t_fontConfig.F = game_config["font"]["file"];
		t_fontConfig.S = game_config["font"]["size"];
		t_fontConfig.R = game_config["font"]["color"].at(0);	
		t_fontConfig.G = game_config["font"]["color"].at(1);
		t_fontConfig.B = game_config["font"]["color"].at(2);

		// Set player, enemy, and bullet configurations
		for (auto& a : game_config["entity"].items())
		{
			EntityConfig temp;
		
			temp.T = a.key();
			temp.SR = game_config["entity"][temp.T]["shape_radius"];
			temp.CR = game_config["entity"][temp.T]["collision_radius"];
			temp.SMin = game_config["entity"][temp.T]["speed"].at(0);
			temp.SMax = game_config["entity"][temp.T]["speed"].at(1);
			temp.FR = game_config["entity"][temp.T]["fill_color"].at(0);	
			temp.FG = game_config["entity"][temp.T]["fill_color"].at(1);		
			temp.FB = game_config["entity"][temp.T]["fill_color"].at(2);	
			temp.OR = game_config["entity"][temp.T]["outline_color"].at(0);	
			temp.OG = game_config["entity"][temp.T]["outline_color"].at(1);		
			temp.OB = game_config["entity"][temp.T]["outline_color"].at(2);		
			temp.OT = game_config["entity"][temp.T]["outline_thickness"];
			temp.VMin = game_config["entity"][temp.T]["vertices"].at(0);		
			temp.VMax = game_config["entity"][temp.T]["vertices"].at(1);
			temp.SL = game_config["entity"][temp.T]["spawn_lifespan"];	
			temp.SI = game_config["entity"][temp.T]["spawn_interval"];	
			
			if (temp.T == "player")
				t_playerConfig = temp;
			if (temp.T == "enemy")
				t_enemyConfig = temp;
			if (temp.T == "bullet")
				t_bulletConfig = temp;
		}

		// Set asset configurations
		t_terrainConfig.F = game_config["terrain"]["file"];
		t_terrainConfig.N = game_config["terrain"]["name"];
		t_terrainConfig.D = game_config["terrain"]["difficulty"];
		
		// Load and verify font can be loaded, if not, print an error message
		if (!m_font.loadFromFile(m_fontConfig.F))
		{
			std::cerr << "Could not load font!\n";
			exit(-1);
		}
		
		// Load and verify terrain texture can be loaded, if not, print an error message
		if (!m_terrain.loadFromFile(m_terrainConfig.F))
		{
			std::cerr << "Could not load terrain texture!\n";
			exit(-1);
		}

		return configObject(t_windowConfig, t_fontConfig, t_textConfig, t_playerConfig, t_enemyConfig, t_bulletConfig, t_terrainConfig);
	}

}; // End namespace