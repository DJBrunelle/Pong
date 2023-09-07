#pragma once
#include "Rectangle.h"

class Paddle : public Rectangle
{
public:
	Paddle(float xPos) : Rectangle(Rectangle::RectType::paddle,Vector2(xPos, 310)) {}

	void Input(bool up, bool down);

	void Update(Time* time) override;
	void Render(sf::RenderWindow* window) override;

	float speed = 250.f;

private:
	bool upInput;
	bool downInput;
};
