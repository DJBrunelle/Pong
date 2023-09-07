#pragma once
#include <string>
#include <vector>

#include "Time.h"

class ShapeOnTheLoose;
class Rectangle;
class Ball;
class Paddle;

namespace sf
{
	class RenderWindow;
}

class GameObject;

class Pong
{
public:

	Pong();
	~Pong();

	Ball* ball;

	Paddle* paddleLeft;
	Paddle* paddleRight;

	Rectangle* upperBound;
	Rectangle* lowerBound;
	Rectangle* leftBound;
	Rectangle* rightBound;

	ShapeOnTheLoose* loosey;

	std::string txtWin = "You Win!";
	std::string txtLose = "You Lose!";
	std::string txtRestart = "Press Enter to restart";
	std::string txtQuit = "Press Escape to quit";

	std::string txtTitle = "Pong - Target Practice";
	std::string txtInstructions1 = "Hit the red square that's on the loose!";
	std::string txtInstructions2 = "Controls";
	std::string txtInstructions3 = "Left Paddle: W/S";
	std::string txtInstructions4 = "Right Paddle: Up/Down";



	bool showWin = false;
	bool showLose = false;
	bool showRestart = false;
	bool showQuit = false;
	bool showIntructions = false;

	void Win();
	void Lose();
	void Pause();
	void Play();

	Time* time;

	bool p1up;
	bool p1down;
	bool p2up;
	bool p2down;

	bool won = false;

	void InputP1();
	void InputP2();

	void HandleCollision(Ball* ball, Rectangle* rect);
	void HandleCollision(ShapeOnTheLoose* loosey, Rectangle* rect);

	void Restart();
	void Stop(sf::RenderWindow* window);

	struct GameState
	{
		std::vector<GameObject*> gameObjects;
	};

	GameState gameState;

	void Update();
	void Render(sf::RenderWindow* window);
};

