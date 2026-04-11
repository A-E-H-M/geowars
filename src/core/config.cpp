#include <string>
#include <iostream>
#include <fstream>

#include <nlohmann/json.hpp>

#include "geowars/config_components.hpp"
#include "geowars/config.hpp"

namespace GWars 
{
	using json = nlohmann::json;

    json configParse(const std::string& file_path)
	{
    	// Verify config file can be located and parsed, if not, print an error message
		try
		{
			std::ifstream f(file_path);
			json jObject = json::parse(f);
			return jObject;
        }

		catch (const json::parse_error& temp_value)
		{
			std::cout << "Message: Couldn't open config file for reading. \n"
					<< "Error: " << temp_value.what() << "Exception ID: " << temp_value.id << "\n";
			exit(-1);
			return NULL;
		}
	}

	configObject configInit(const json& game_config) 
	{

		WindowConfig t_windowConfig_1;

		TextConfig t_textConfig_1;
		TextConfig t_textConfig_2;
		TextConfig t_textConfig_3;

		
		FontConfig t_fontConfig_1;
		FontConfig t_fontConfig_2;

		TextureConfig t_textureConfig_1;
		TextureConfig t_textureConfig_2;
		TextureConfig t_textureConfig_3;
		

		EntityConfig t_entityConfig_1;
		EntityConfig t_entityConfig_2;
		EntityConfig t_entityConfig_3;
		
		TerrainConfig t_terrainConfig_1;
		
		// Set window configurations
		t_windowConfig_1.width = game_config["window_spec"]["width"];
		t_windowConfig_1.height = game_config["window_spec"]["height"];
		t_windowConfig_1.frame_rate = game_config["window_spec"]["frame_rate"];
		t_windowConfig_1.fullscreen_mode = game_config["window_spec"]["fullscreen"];
		
		// Set on screen text strings
		for (auto& d : game_config["text"].items()) // Looping through "text" values ("window", "score")
		{
			TextConfig temp;
			
			// Set window and score
			for (auto& t : d.value().items())
			{
				auto element_num = t.value();

				temp.text = element_num["text_1"];
				temp.text_size = element_num["size"];
				temp.font = element_num["font"];
				temp.text_color.color_R = element_num["color"].at(0);
				temp.text_color.color_G = element_num["color"].at(1);
				temp.text_color.color_B = element_num["color"].at(2);

				
				if (d.value() == "window") 
				{
					t_textConfig_1 = temp;
				}
				else if (d.value() == "score")
				{
					if  (element_num == "element_1")
						t_textConfig_2 = temp;
					else if  (element_num == "element_2")
						t_textConfig_3 = temp;
				}
			}

		}

		// Set font configurations
		for (auto& c : game_config["fonts"].items())
		{
			auto temp_string = c.key();
			auto temp_value = c.value();

			if (temp_string == "font_1")
			{
				t_fontConfig_1.font_file_path = temp_value["file"];
			}
			else if (temp_string == "font_2")
			{
				t_fontConfig_2.font_file_path = temp_value["file"];
			}
		}

		// Set texture configurations
		for (auto& t : game_config["textures"].items())
		{
			auto temp_String = t.key();
			auto temp_value = t.value();

			if (temp_String == "texture_1")
			{
				t_textureConfig_1.texture_file = temp_value["file"];				
				t_textureConfig_1.texture_name = temp_value["name"];
			}
			else if (temp_String == "texture_2")
			{
				t_textureConfig_2.texture_file = temp_value["file"];
				t_textureConfig_2.texture_name = temp_value["name"];
			}
			else if (temp_String == "texture_3")
			{
				t_textureConfig_3.texture_file = temp_value["file"];
				t_textureConfig_3.texture_name = temp_value["name"];
			}
			else
			{
				std::cout << "not found   ";
			}
		}
		
		// Set player, enemy, and bullet configurations
		for (auto& e : game_config["entity"].items())
		{
			EntityConfig temp;
			
			auto temp_string = e.key();
			auto temp_value = e.value();

			temp.shape_radius = temp_value["shape_radius"];
			temp.collision_radius = temp_value["collision_radius"];
			temp.speed_min = temp_value["speed"].at(0);
			temp.speed_max = temp_value["speed"].at(1);
			temp.fill_color.color_R = temp_value["fill_color"].at(0);	
			temp.fill_color.color_G = temp_value["fill_color"].at(1);		
			temp.fill_color.color_B = temp_value["fill_color"].at(2);	
			temp.outline_color.color_R = temp_value["outline_color"].at(0);	
			temp.outline_color.color_G = temp_value["outline_color"].at(1);		
			temp.outline_color.color_B = temp_value["outline_color"].at(2);		
			temp.outline_thickness = temp_value["outline_thickness"];
			temp.vertices_min = temp_value["vertices"].at(0);		
			temp.vertices_max = temp_value["vertices"].at(1);
			temp.spawn_life = temp_value["spawn_lifespan"];	
			temp.spawn_interval = temp_value["spawn_interval"];
			temp.texture = temp_value["texture"];

			if (temp_string == "player")
			{
				t_entityConfig_1 = temp;
			}
			else if (temp_string == "enemy")
			{
				t_entityConfig_2 = temp;
			}
			else if (temp_string == "bullet")
			{
				t_entityConfig_3 = temp;
			}
			
		}

		// Set terrain configurations
		t_terrainConfig_1.texture = game_config["terrain"]["texture"];
		t_terrainConfig_1.terrain_type = game_config["terrain"]["type"];
		t_terrainConfig_1.difficulty = game_config["terrain"]["difficulty"];
		
		
		// Load and verify font can be loaded, if not, print an error message
		// if (!m_font.loadFromFile(t_fontConfig_1.font_file_name))
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
							t_terrainConfig_1
							);
	}

	configObject Init(const std::string& file_path)
	{
		auto parsed_json = configParse(file_path);
		return configInit(parsed_json);
	}

} // End namespace