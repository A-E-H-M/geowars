#pragma once

#include <string>
#include <string_view>

namespace GWars
{	
	// Settings for RGB color values. The default value set for each is 255.
	struct Color
	{	
		// R value in RGB scale. Default value is 255.
		int color_R{255};
		// G value in RGB scale. Default value is 255.
		int color_G{255};
		// B value in RGB scale. Default value is 255.
		int color_B{255};

		Color(){};
		Color(int R, int G, int B) : color_R(R), color_G(G), color_B(B) {}
	};

	// Window configuration properties (Width, Height, Frame Rate, ...)
	struct WindowConfig
	{
		// Width of game window
		int width{0};
		// Height of game window
		int height{0};
		// Frame-rate limit for window
		int frame_rate{0};
		// Full-screen mode option
		// 0 is true, 1 is false
		bool fullscreen_mode{false};
		// Background color in window in RGB scale. Default values are set to 0, 0, 0.
		Color window_color{0, 0, 0};
		// Text on the top of the window bar
		std::string window_title;

		WindowConfig(){};

		WindowConfig(int W, int H, int FR, int FSM) 
			: width(W), height(H), frame_rate(FR), fullscreen_mode(FSM) 
			{}

		WindowConfig(int W, int H, int FR, int FSM, int R, int G, int B, std::string_view WT) 
			: width(W), height(H), frame_rate(FR), fullscreen_mode(FSM), window_color(R, G, B), window_title(WT)
			{}

		private:
		
	};

	// Font configuration properties (File path, Size, RGB color values)
	struct FontConfig
	{
		// String file path to the font file.
		std::string font_file_path;

		FontConfig(){};

		FontConfig(std::string_view F)
			: font_file_path(F) {}
	};

	// Text configuration properties (Text String, Size, RGB color values)
	struct TextConfig
	{
		// The text string
		std::string text;
		// Size of the text. Default size is 0.
		int text_size{0};
		// Color values for the color of the font for RGB
		Color text_color;
		
		TextConfig(){};

		TextConfig(std::string_view T)
			: text(T) 
			{};
		TextConfig(std::string_view T, int TS, int R, int G, int B)
			: text(T), text_size(TS), text_color(R, G, B) {}
	};

	struct EntityConfig
	{
		// Name of the type of entity
		std::string entity_type;
		// The radius of the entity. The default value is set to 0.
		int shape_radius{0};
		// The collision of the radius for the entity. The default value is set to 0.
		int collision_radius{0};
		// Entity's minimum speed. The default value is set to 0.
		int speed_min{0};
		// Entity's maximum speed. The default value is set to 0.
		int speed_max{0};
		// The color fill of the entity in RGB scale. The default values are set to 225.
		Color fill_color;
		// The outline color of the entity in RGB scale. The default values are set to 255.
		Color outline_color;
		// The thickness of the entity. The default value is set to 3.
		int outline_thickness{3};
		// The entity's minimum vertices. The default value is set to 3.
		int vertices_min{3};
		// The entity's maximum vertices. The default value is set to 3.
		int vertices_max{3};
		// The entity's life time on screen after spawning. The default value is set to 0.
		int spawn_life{0};
		// How often the the entity will spawn again. The default value is set to 0.
		int spawn_interval{0};

		EntityConfig(){};

		EntityConfig(std::string_view T, int SR, int CR, int SMin, int SMax, int FR, int FG, int FB, int OR, int OG, int OB, int OT, int VMin, int VMax, int SL, int SI)
		: entity_type(T), shape_radius(SR), collision_radius(CR), speed_min(SMin), speed_max(SMax), fill_color(FR, FG, FB), outline_color(OR, OG, OB), outline_thickness(OT), vertices_min(VMin), vertices_max(VMax), spawn_life(SL), spawn_interval(SI)
		{}
	};

	// Terrain configuration properties (File path, Name, Difficulty)
	struct TerrainConfig
	{
		// The file path name to the terrain asset.
		std::string terrain_file_path;
		// Name of the terrain type.
		std::string terrain_type;
		// The level of difficulty for the terrain. The default value is set to 0.
		int difficulty{0};

		TerrainConfig(){};

		TerrainConfig(std::string_view F, std::string_view N, int D)
			: terrain_file_path(F), terrain_type(N), difficulty(D)
			{}
	};
}; // End namespace