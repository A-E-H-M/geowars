#include <string>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

#include "geowars/config_components.hpp"
#include "geowars/config.hpp"

namespace GWars 
{
	using json = nlohmann::json;

    json GameConfig::configParse()
	{
    	// Verify config file can be located and parsed, if not, print an error message
		try
		{
			std::ifstream f(ConfigFilePath);
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
		json game_config = configParse();
		
		WindowConfig t_windowConfig_1;

		FontConfig t_fontConfig_1;
		FontConfig t_fontConfig_2;

		TextConfig t_textConfig_1;
		TextConfig t_textConfig_2;
		TextConfig t_textConfig_3;

		TextureConfig t_textureConfig_1;
		TextureConfig t_textureConfig_2;
		TextureConfig t_textureConfig_3;

		EntityConfig t_entityConfig_1;
		EntityConfig t_entityConfig_2;
		EntityConfig t_entityConfig_3;
		
		TerrainConfig t_terrainConfig_1;

		// Set window configurations
		t_windowConfig_1.width = game_config["window"]["width"];
		t_windowConfig_1.height = game_config["window"]["height"];
		t_windowConfig_1.frame_rate = game_config["window"]["frame_rate"];
		t_windowConfig_1.fullscreen_mode = game_config["window"]["fullscreen"];	

		// Set on screen text strings
		for (auto& d : game_config["text"].items())
		{
			TextConfig temp;
			std::string text_loc = d.key();
			std::string tempKey = d.key();
			
			for (auto& e : d.value().items())
			{
				std::string element_temp = e.key();

				temp.text = game_config["text"][text_loc][element_temp]["text_1"];
				temp.font = game_config["text"][text_loc][element_temp]["font"];
				temp.text_size = game_config["text"][text_loc][element_temp]["size"];
				temp.text_color.color_R = game_config["text"][text_loc][element_temp]["color"].at(0);
				temp.text_color.color_G = game_config["text"][text_loc][element_temp]["color"].at(0);
				temp.text_color.color_B = game_config["text"][text_loc][element_temp]["color"].at(0);

				
				if (tempKey == "window") 
				{
					t_textConfig_1 = temp;
				}
				else if (tempKey == "score")
				{
					if (element_temp == "element_1")
						t_textConfig_2 = temp;
					if (element_temp == "element_2")
						t_textConfig_3 = temp;
				}
			}

		}

		// Set font configurations
		for (auto& c : game_config["font"].items())
		{
			std::string tempKey = c.key();

			if (tempKey == "font_1")
			{
				t_fontConfig_1.font_file_path = game_config["font"][tempKey]["file"];
			}
			else if (tempKey == "font_2")
			{
				t_fontConfig_2.font_file_path = game_config["font"][tempKey]["file"];
			}
		}

		// Set texture configurations
		for (auto& c : game_config["textures"].items())
		{
			std::string tempKey = c.key();
			
			if (tempKey == "texture_1")
			{
				t_textureConfig_1.texture_file = game_config["textures"][tempKey]["file"];
				t_textureConfig_1.texture_name = game_config["textures"][tempKey]["name"];
			}
			else if (tempKey == "texture_2")
			{
				t_textureConfig_2.texture_file = game_config["textures"][tempKey]["file"];
				t_textureConfig_2.texture_name = game_config["textures"][tempKey]["name"];
			}
			else if (tempKey == "texture_3")
			{
				t_textureConfig_3.texture_file = game_config["textures"][tempKey]["file"];
				t_textureConfig_3.texture_name = game_config["textures"][tempKey]["name"];
			}
		}

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
			temp.texture = game_config["entity"][temp.entity_type]["texture"];

			if (temp.entity_type == "player")
			{
				t_entityConfig_1 = temp;
			}
			else if (temp.entity_type == "enemy")
			{
				t_entityConfig_2 = temp;
			}
			else if (temp.entity_type == "bullet")
			{
				t_entityConfig_3 = temp;
			}
		}

		// Set asset configurations
		t_terrainConfig_1.texture = game_config["terrain"]["texture"];
		t_terrainConfig_1.terrain_type = game_config["terrain"]["type"];
		t_terrainConfig_1.difficulty = game_config["terrain"]["difficulty"];
		
		// Load and verify font can be loaded, if not, print an error message
		// if (!m_font.loadFromFile(t_fontConfig_1.font_file_path))
		// {
		//	std::cerr << "Could not load font!\n";
		//	exit(-1);
		// }
		
		// Load and verify terrain texture can be loaded, if not, print an error message
		// if (!m_terrain.loadFromFile(t_terrainConfig_1.terrain_file_path))
		// {
		//	std::cerr << "Could not load terrain texture!\n";
		//	exit(-1);
		// }

		return configObject(t_windowConfig_1, t_fontConfig_1, t_fontConfig_2,
							t_textConfig_1, t_textConfig_2, t_textConfig_3,
							t_textureConfig_1, t_textureConfig_2, t_textureConfig_3,
							t_entityConfig_1, t_entityConfig_2, t_entityConfig_3,
							t_terrainConfig_1);
	}
} // End namespace