#pragma once
#include "GameObject.h"

namespace sf
{
	class RenderWindow;
}

class Ball : public GameObject
{
public:

	Vector2 direction = Vector2(1.f,0.f);

	float radius = 30.f;

	Vector2 center = Vector2(0.f, 0.f);

	float speed = 200.f;

	Ball() : GameObject(Vector2(640, 500)) {}
	void Update(Time* time) override;
	void Render(sf::RenderWindow* window) override;
};

