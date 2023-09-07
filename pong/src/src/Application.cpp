#include "Application.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Window.hpp>

#include "Pong.h"

void Application::Run(int width, int height)
{
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(width, height), "Pong - Target Practice", sf::Style::Titlebar | sf::Style::Close);

    Pong pong;

    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.scancode == sf::Keyboard::Scan::W)
                {
                    pong.p1up = true;
                }
                if (event.key.scancode == sf::Keyboard::Scan::S)
                {
                    pong.p1down = true;
                }
                if (event.key.scancode == sf::Keyboard::Scan::Up)
                {
                    pong.p2up = true;
                }
                if (event.key.scancode == sf::Keyboard::Scan::Down)
                {
                    pong.p2down = true;
                }
                if (event.key.scancode == sf::Keyboard::Scan::Enter)
                {
                    pong.Restart();
                }
                if (event.key.scancode == sf::Keyboard::Scan::Escape)
                {
                    pong.Stop(window);
                }
            }
            if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.scancode == sf::Keyboard::Scan::W)
                {
                    pong.p1up = false;
                }
                if (event.key.scancode == sf::Keyboard::Scan::S)
                {
                    pong.p1down = false;
                }
                if (event.key.scancode == sf::Keyboard::Scan::Up)
                {
                    pong.p2up = false;
                }
                if (event.key.scancode == sf::Keyboard::Scan::Down)
                {
                    pong.p2down = false;
                }
            }
        }
        pong.Update();
        window->clear();
        pong.Render(window);
        window->display();
    }

    delete window;
}
