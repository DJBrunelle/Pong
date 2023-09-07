#pragma once
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

class Time
{
public:

	Time();

	void Update();
	void Stop();
	void Start();

	bool isStopped = false;

	sf::Time maxDeltaTime = sf::seconds(0.33f);

	sf::Time deltaTime = sf::seconds(0.f);
	sf::Time time = sf::seconds(0.f);

private:
	float timeScale = 1.f;
	sf::Clock curDeltaTime;
};
