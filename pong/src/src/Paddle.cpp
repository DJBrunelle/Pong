#include "Paddle.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "Time.h"


void Paddle::Input(bool up, bool down)
{
	this->upInput = up;
	this->downInput = down;
}

void Paddle::Update(Time* time)
{
	Rectangle::Update(time);

	Vector2 direction(0.f, 0.f);

	if (upInput)
	{
		direction.y -= 1;
	}
	if (downInput)
	{
		direction.y += 1;
	}

	if (position.y < 10 && direction.y < 0)
	{
		return;
	}
	if (position.y > 610 && direction.y > 0)
	{
		return;
	}
	this->position += direction * speed * time->deltaTime.asSeconds();
}

void Paddle::Render(sf::RenderWindow* window)
{
	sf::RectangleShape rect(sf::Vector2f(width, height));
	rect.setPosition(position.x, position.y);
	rect.setFillColor(sf::Color::White);
	window->draw(rect);

	botLeft = Vector2(rect.getGlobalBounds().left, rect.getGlobalBounds().top + rect.getGlobalBounds().height);
	topRight = Vector2(rect.getGlobalBounds().left + rect.getGlobalBounds().width, rect.getGlobalBounds().top);

}
