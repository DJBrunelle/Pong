#include "Rectangle.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

void Rectangle::Update(Time* time)
{
	center = Vector2(position.x + (width*0.5f), position.y + (height*0.5f));
}

void Rectangle::Render(sf::RenderWindow* window)
{
	sf::RectangleShape rect(sf::Vector2f(width, height));
	rect.setPosition(position.x, position.y);
	rect.setFillColor(sf::Color::Green);
	window->draw(rect);

	botLeft = Vector2(rect.getGlobalBounds().left, rect.getGlobalBounds().top + rect.getGlobalBounds().height);
	topRight = Vector2(rect.getGlobalBounds().left + rect.getGlobalBounds().width, rect.getGlobalBounds().top);
}
