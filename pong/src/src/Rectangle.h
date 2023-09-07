#pragma once
#include "GameObject.h"

class Rectangle: public GameObject
{
public:
	enum RectType { out, wall, paddle, objective };

	RectType rectType;

	float width = 30;
	float height = 100;

	Rectangle(RectType rectType, Vector2 pos) : GameObject(pos) { this->rectType = rectType; }

	Rectangle(RectType rectType,Vector2 pos, float width, float height) : GameObject(pos)
	{
		this->width = width;
		this->height = height;
		this->rectType = rectType;
	}

	

	Vector2 center = Vector2(0.f, 0.f);

	Vector2 botLeft = Vector2(0.f,0.f);
	Vector2 topRight = Vector2(0.f, 0.f);

	void Update(Time* time) override;
	void Render(sf::RenderWindow* window) override;
};
