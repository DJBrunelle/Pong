#include "Ball.h"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "Time.h"


void Ball::Update(Time* time)
{
	position += Normalize(direction) * speed * time->deltaTime.asSeconds();
	center = Vector2(position.x + radius, position.y + radius);
}

void Ball::Render(sf::RenderWindow* window)
{
	sf::CircleShape ball(radius);
	ball.setPosition(position.x, position.y);
	ball.setFillColor(sf::Color::Green);
	window->draw(ball);
}
