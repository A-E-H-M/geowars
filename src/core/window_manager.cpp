#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "geowars/window_manager.hpp"
#include "geowars/game.hpp"

namespace GWars
{
	/*
	std::shared_ptr<sf::RenderWindow> Window_Manager::add_window(const WindowConfig& _window)
	{
		auto w_window = std::shared_ptr<sf::RenderWindow>(new sf::RenderWindow);
		w_window->create(sf::VideoMode(_window.width, _window.height), _window.window_title);
		w_window->setFramerateLimit(_window.frame_rate);
		all_windows.push_back(w_window);
		return w_window;
	}
*/
	void Window_Manager::initWindow(class Game& game)
	{
		game.m_window.create(sf::VideoMode(game.m_windowConfig.width, game.m_windowConfig.height), game.m_textConfig.text);
		game.m_window.setFramerateLimit(game.m_windowConfig.frame_rate);
	}

	void Window_Manager::pollWindowEvents(class Game& game)
	{
		sf::Event event;

        while (game.m_window.pollEvent(event))
        {
			game.m_input.userInput(event, game);
		}
	}
} // End namespace