#include "geowars/window_manager.hpp"
#include "geowars/input.hpp"

namespace GWars
{
	std::shared_ptr<sf::RenderWindow> Window_Manager::add_window(const WindowConfig& _window)
	{
		auto w_window = std::shared_ptr<sf::RenderWindow>(new sf::RenderWindow);
		w_window->create(sf::VideoMode(_window.width, _window.height), _window.window_title);
		w_window->setFramerateLimit(_window.frame_rate);
		all_windows.push_back(w_window);
		return w_window;
	}

	/*	
	void pullWindowEvents(const sf::RenderWindow& m_window)
	{
		sf::Event event;

        while (m_window.pollEvent(event))
        {
			userInput(event);
		}
	}
		*/
} // End namespace