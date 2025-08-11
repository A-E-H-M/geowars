#include <string>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

#include "../../include/geowars/config_components.hpp"
#include "../../include/geowars/config.hpp"

using json = nlohmann::json;

namespace GWars 
{
    json GameConfig::configParse(const std::string& textString)
	{
    	// Verify config file can be located and parsed, if not, print an error message
		try
		{
			std::ifstream f(textString);
			json jObject = json::parse(f);
			return jObject;
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
		t_windowConfig.width = game_config["window"]["width"];
		t_windowConfig.height = game_config["window"]["height"];
		t_windowConfig.frame_rate = game_config["window"]["frame_rate"];
		t_windowConfig.full_screen_mode = game_config["window"]["fullscreen"];	

		// Set on screen text strings
		t_textConfig.text = game_config["text"]["window_text"];

		// Set font configurations
		t_fontConfig.font_file_path = game_config["font"]["file"];
		t_textConfig.text_size = game_config["font"]["size"];
		t_textConfig.text_color.color_R = game_config["font"]["color"].at(0);	
		t_textConfig.text_color.color_G = game_config["font"]["color"].at(1);
		t_textConfig.text_color.color_B = game_config["font"]["color"].at(2);

		// Set player, enemy, and bullet configurations
		for (auto& a : game_config["entity"].items())
		{
			EntityConfig temp;
		
			temp.entity_type = a.key();
			temp.shape_radius = game_config["entity"][temp.entity_type]["shape_radius"];
			temp.collision_radius = game_config["entity"][temp.entity_type]["collision_radius"];
			temp.speed_min = game_config["entity"][temp.entity_type]["speed"].at(0);
			temp.speed_max = game_config["entity"][temp.entity_type]["speed"].at(1);
			temp.fill_color.color_R = game_config["entity"][temp.entity_type]["fill_color"].at(0);	
			temp.fill_color.color_G = game_config["entity"][temp.entity_type]["fill_color"].at(1);		
			temp.fill_color.color_B = game_config["entity"][temp.entity_type]["fill_color"].at(2);	
			temp.outline_color.color_R = game_config["entity"][temp.entity_type]["outline_color"].at(0);	
			temp.outline_color.color_G = game_config["entity"][temp.entity_type]["outline_color"].at(1);		
			temp.outline_color.color_B = game_config["entity"][temp.entity_type]["outline_color"].at(2);		
			temp.outline_thickness = game_config["entity"][temp.entity_type]["outline_thickness"];
			temp.vertices_min = game_config["entity"][temp.entity_type]["vertices"].at(0);		
			temp.vertices_max = game_config["entity"][temp.entity_type]["vertices"].at(1);
			temp.spawn_life = game_config["entity"][temp.entity_type]["spawn_lifespan"];	
			temp.spawn_interval = game_config["entity"][temp.entity_type]["spawn_interval"];	
			
			if (temp.entity_type == "player")
				t_playerConfig = temp;
			if (temp.entity_type == "enemy")
				t_enemyConfig = temp;
			if (temp.entity_type == "bullet")
				t_bulletConfig = temp;
		}

		// Set asset configurations
		t_terrainConfig.terrain_file_path = game_config["terrain"]["file"];
		t_terrainConfig.terrain_type = game_config["terrain"]["name"];
		t_terrainConfig.difficulty = game_config["terrain"]["difficulty"];
		
		// Load and verify font can be loaded, if not, print an error message
		// if (!m_font.loadFromFile(t_fontConfig.font_file_path))
		// {
		//	std::cerr << "Could not load font!\n";
		//	exit(-1);
		// }
		
		// Load and verify terrain texture can be loaded, if not, print an error message
		// if (!m_terrain.loadFromFile(t_terrainConfig.terrain_file_path))
		// {
		//	std::cerr << "Could not load terrain texture!\n";
		//	exit(-1);
		// }

		return configObject(t_windowConfig, t_fontConfig, t_textConfig, t_playerConfig, t_enemyConfig, t_bulletConfig, t_terrainConfig);
	}

}; // End namespace