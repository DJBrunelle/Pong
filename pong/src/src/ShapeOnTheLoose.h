#pragma once
#include <random>

#include "Rectangle.h"

class ShapeOnTheLoose : public Rectangle
{
public:
	Vector2 direction;
    float speed = 100.f;

	ShapeOnTheLoose(Vector2 start) : Rectangle(objective, start, 20, 20)
	{
        // Create a random device
        std::random_device rd;
        // Initialize a random number generator engine
        std::mt19937 engine(rd());
        // Define a uniform real distribution between 0.0 and 1.0
        std::uniform_real_distribution<float> dist1(-1.0, 1.0);
        std::uniform_real_distribution<float> dist2(-1.0, 1.0);
        // Generate a random float
        float rand1 = dist1(engine);
        float rand2 = dist2(engine);

        direction = Normalize(Vector2(rand1, rand2));

	}

    void Update(Time* time) override;
    void Render(sf::RenderWindow* window) override;

};
