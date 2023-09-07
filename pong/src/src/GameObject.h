#pragma once
#include "Vector2.h"

class Time;

namespace sf
{
	class RenderWindow;
}

class GameObject
{
public:
	GameObject(Vector2 position);
	virtual ~GameObject() = default;

	Vector2 position;

	virtual void Update(Time* time);
	virtual void Render(sf::RenderWindow* window);

};

