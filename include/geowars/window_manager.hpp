#pragma once

#include <vector>
#include <memory>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

namespace GWars
{
	// Template vector for storing SFML window objects
	using WindowVec = std::vector<std::shared_ptr<sf::RenderWindow>>;

	// Manages all windows
	class Window_Manager 
	{
		private:
			// Named vector for all windows
			WindowVec all_windows;

		public:
			Window_Manager(){};
			// Add a window to the vector of windows based on the window configuration passed by reference
			//std::shared_ptr<sf::RenderWindow> add_window(const WindowConfig& _window);
			void initWindow(class Game& game);
			void pollWindowEvents(class Game& game);

	};
} // End namespace