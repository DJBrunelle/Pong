#include "ShapeOnTheLoose.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "Time.h"

void ShapeOnTheLoose::Update(Time* time)
{
	position += Normalize(direction) * speed * time->deltaTime.asSeconds();
	Rectangle::Update(time);
}

void ShapeOnTheLoose::Render(sf::RenderWindow* window)
{
	sf::RectangleShape rect(sf::Vector2f(width, height));
	rect.setPosition(position.x, position.y);
	rect.setFillColor(sf::Color::Red);
	window->draw(rect);

	botLeft = Vector2(rect.getGlobalBounds().left, rect.getGlobalBounds().top + rect.getGlobalBounds().height);
	topRight = Vector2(rect.getGlobalBounds().left + rect.getGlobalBounds().width, rect.getGlobalBounds().top);

}
