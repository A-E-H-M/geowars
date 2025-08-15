#include <SFML/System.hpp>

#include "geowars/game.hpp"

namespace GWars
{
    // Assess for user input
    void Input::userInput(const sf::Event& event, class Game& game) 
    {	
        switch (event.type)
            {
                // Event triggers the window to closed
                case sf::Event::Closed:
                    game.m_running = false;
                    break;
                // Event is triggered when a key is pressed
                case sf::Event::KeyPressed:
                    keyboardPressed(event, game);
                    break;
                // Event is triggered when a key is released
                case sf::Event::KeyReleased:
                    keyboardReleased(event, game);
                    break;
                // Event is triggered when a mouse key is pressed
                case sf::Event::MouseButtonPressed:
                    mouseButtonPressed(event, game);
                    break;
                default:
                    break;
            }
    }

    // Event is triggered when a key is pressed
    void Input::keyboardPressed(const sf::Event& event, class Game& game)
    {
        switch (event.key.code)
        {
            case sf::Keyboard::W:
                game.m_player->cInput->up = true;
                break;
            case sf::Keyboard::S:
                game.m_player->cInput->down = true;
                break;
            case sf::Keyboard::A:
                game.m_player->cInput->left = true;
                break;
            case sf::Keyboard::D:
                game.m_player->cInput->right = true;
                break;
            case sf::Keyboard::Space:
                game.setPaused();
                break;
            case sf::Keyboard::Escape:
                game.m_running = false;
                break;
            default: break;
        }
    }


    void Input::keyboardReleased(const sf::Event& event, class Game& game)
    {
        switch (event.key.code)
        {
            case sf::Keyboard::W:
                game.m_player->cInput->up = false;
                break;
            case sf::Keyboard::S:
                game.m_player->cInput->down = false;
                break;
            case sf::Keyboard::A:
                game.m_player->cInput->left = false;
                break;
            case sf::Keyboard::D:
                game.m_player->cInput->right = false;
                break;
            default: break;
        }
    }


    void Input::mouseButtonPressed(const sf::Event& event, class Game& game)
    {
        switch (event.mouseButton.button)
        {
            case sf::Mouse::Left:
                game.spawnBullet(game.m_player, Vec2(event.mouseButton.x, event.mouseButton.y));
                break;
            case sf::Mouse::Right:
                //TODO: Spawn special weapon here
                break;
            default:
                break;
        }
    }
} // End namespace