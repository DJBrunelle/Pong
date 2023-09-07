#include "Pong.h"

#include <iostream>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

#include "Ball.h"
#include "GameObject.h"
#include "Paddle.h"
#include "ShapeOnTheLoose.h"

bool CheckCollision(Ball* ball, Rectangle* rect)
{
	float circleDistanceX = abs(ball->center.x - rect->center.x);
	float circleDistanceY = abs(ball->center.y - rect->center.y);

	if (circleDistanceX > (rect->width / 2 + ball->radius)) {
		return false;
	}
	if (circleDistanceY > (rect->height / 2 + ball->radius)) {
		return false;
	}

	if (circleDistanceX <= (rect->width / 2)) {
		return true;
	}
	if (circleDistanceY <= (rect->height / 2)) {
		return true;
	}

	float cornerDistanceSq = pow(circleDistanceX - rect->width / 2, 2) +
		pow(circleDistanceY - rect->height / 2, 2);

	return (cornerDistanceSq <= pow(ball->radius, 2));
}

bool CheckCollision(Rectangle* rect1, Rectangle* rect2) {
	if (rect1->center.x + rect1->width * 0.5 <= rect2->center.x - rect2->width * 0.5   || // left
		rect1->center.x - rect1->width * 0.5 >= rect2->center.x + rect2->width * 0.5   || // right
		rect1->center.y + rect1->height * 0.5 <= rect2->center.y - rect2->height * 0.5 || // top
		rect1->center.y - rect1->height * 0.5 >= rect2->center.y + rect2->height * 0.5) { // bottom
		return false; // No collision
	}
	return true; // Collision
}
void Pong::HandleCollision(Ball* ball, Rectangle* rect)
{

	if (CheckCollision(ball, rect))
	{

		Vector2 direction = ball->center - rect->center;

		if (rect->rectType == Rectangle::RectType::paddle)
		{
			ball->direction = direction;
			ball->speed += 10.f;
		}
		else if (rect->rectType == Rectangle::RectType::wall)
		{
			ball->direction = Vector2(ball->direction.x, -ball->direction.y);
		}
		else if (rect->rectType == Rectangle::RectType::out)
		{
			// Lose
			Lose();
		}
		else if (rect->rectType == Rectangle::RectType::objective)
		{
			// Win
			Win();
		}
	}
}

void Pong::HandleCollision(ShapeOnTheLoose* loosey, Rectangle* rect)
{
	if (CheckCollision(loosey, rect))
	{
		Vector2 direction = loosey->center - rect->center;

		if (rect->rectType == Rectangle::RectType::paddle)
		{
			loosey->direction = direction;
		}
		else if (rect->rectType == Rectangle::RectType::wall)
		{
			loosey->direction = Vector2(loosey->direction.x, -loosey->direction.y);
		}
		else if (rect->rectType == Rectangle::RectType::out)
		{
			loosey->direction = Vector2(-loosey->direction.x, loosey->direction.y);
		}
	}
}

void Pong::Restart()
{
	ball->position = Vector2(680, 500);
	Play();
}

void Pong::Stop(sf::RenderWindow* window)
{
	if (time->isStopped)
	{
		window->close();
	}
	else
	{
		Pause();
	}
}

Pong::Pong()
{
	//Start clock
	time = new Time();

	//Initialize ball
	ball = new Ball();
	gameState.gameObjects.push_back(ball);

	//Initialize paddles
	paddleLeft = new Paddle(20.f);
	paddleRight = new Paddle(1230.f);
	gameState.gameObjects.push_back(paddleLeft);
	gameState.gameObjects.push_back(paddleRight);

	//Initialize Bounds
	leftBound = new Rectangle(Rectangle::RectType::out,Vector2(-10.f, 0.f), 10, 720);
	rightBound = new Rectangle(Rectangle::RectType::out,Vector2(1280.f, 0.f), 10, 720);
	upperBound = new Rectangle(Rectangle::RectType::wall,Vector2(0.f, -10.f), 1280, 10);
	lowerBound = new Rectangle(Rectangle::RectType::wall,Vector2(0.f, 720.f), 1280, 10);
	gameState.gameObjects.push_back(leftBound);
	gameState.gameObjects.push_back(rightBound);
	gameState.gameObjects.push_back(upperBound);
	gameState.gameObjects.push_back(lowerBound);

	//Initialize Loosey
	loosey = new ShapeOnTheLoose(Vector2(680, 340));
	gameState.gameObjects.push_back(loosey);

	Pause();

}

Pong::~Pong()
{
	delete time;
	delete ball;
	delete paddleLeft;
	delete paddleRight;
	delete rightBound;
	delete leftBound;
	delete upperBound;
	delete lowerBound;
}

void Pong::Win()
{
	showLose = false;
	showWin = true;
	showQuit = true;
	showRestart = true;
	showIntructions = true;
	time->Stop();
}

void Pong::Lose()
{
	showLose = true;
	showWin = false;
	showQuit = true;
	showRestart = true;
	showIntructions = true;
	time->Stop();
}

void Pong::Pause()
{
	showLose = false;
	showWin = false;
	showQuit = true;
	showRestart = true;
	showIntructions = true;
	time->Stop();
}

void Pong::Play()
{
	showLose = false;
	showWin = false;
	showQuit = false;
	showRestart = false;
	showIntructions = false;
	ball->speed = 200.f;
	time->Start();
}

void Pong::InputP1()
{
	paddleLeft->Input(p1up, p1down);
}

void Pong::InputP2()
{
	paddleRight->Input(p2up, p2down);
}

void Pong::Update()
{
	for (auto object : gameState.gameObjects)
	{
		InputP1();
		InputP2();

		object->Update(time);

		Rectangle* rect = dynamic_cast<Rectangle*>(object);
		if (rect != nullptr) {
			HandleCollision(ball, rect);
			HandleCollision(loosey, rect);
		}
	}

	time->Update();
}

void Pong::Render(sf::RenderWindow* window)
{
	for (auto object : gameState.gameObjects)
	{
		object->Render(window);
	}

	//// Declare and load a font
	sf::Font font;
	font.loadFromFile("fonts/NostalgicRetro.otf");


	if (showLose)
	{
		// Create a text
		sf::Text text(txtLose, font);
		text.setCharacterSize(50);
		text.setStyle(sf::Text::Bold);

		sf::FloatRect textRect = text.getLocalBounds();
		text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
		text.setPosition(sf::Vector2f(window->getSize().x / 2.0f, window->getSize().y / 2.0f));

		text.setFillColor(sf::Color::Red);
		text.setPosition(680, 380);
		window->draw(text);
	}

	if (showWin)
	{
		// Create a text
		sf::Text text(txtWin, font);
		text.setCharacterSize(50);
		text.setStyle(sf::Text::Bold);

		sf::FloatRect textRect = text.getLocalBounds();
		text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
		text.setPosition(sf::Vector2f(window->getSize().x / 2.0f, window->getSize().y / 2.0f));

		text.setFillColor(sf::Color::Green);
		text.setPosition(680, 380);
		window->draw(text);
	}

	if (showRestart)
	{
		// Create a text
		sf::Text text(txtRestart, font);
		text.setCharacterSize(30);
		text.setStyle(sf::Text::Bold);

		sf::FloatRect textRect = text.getLocalBounds();
		text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
		text.setPosition(sf::Vector2f(window->getSize().x / 2.0f, window->getSize().y / 2.0f));


		text.setFillColor(sf::Color::White);
		text.setPosition(680, 420);
		window->draw(text);
	}

	if (showQuit)
	{
		// Create a text
		sf::Text text(txtQuit, font);
		text.setCharacterSize(30);
		text.setStyle(sf::Text::Bold);

		// Calculate the position to center the text
		sf::FloatRect textRect = text.getLocalBounds();
		text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
		text.setPosition(sf::Vector2f(window->getSize().x / 2.0f, window->getSize().y / 2.0f));

		text.setFillColor(sf::Color::White);
		text.setPosition(680, 450);
		window->draw(text);
	}

	if (showIntructions)
	{
		// Create a text
		sf::Text text1(txtTitle, font);
		text1.setCharacterSize(40);
		text1.setStyle(sf::Text::Bold);

		// Calculate the position to center the text
		sf::FloatRect textRect1 = text1.getLocalBounds();
		text1.setOrigin(textRect1.left + textRect1.width / 2.0f, textRect1.top + textRect1.height / 2.0f);
		text1.setPosition(sf::Vector2f(window->getSize().x / 2.0f, window->getSize().y / 2.0f));

		text1.setFillColor(sf::Color::Yellow);
		text1.setPosition(680, 30);
		window->draw(text1);

		// Create a text
		text1 = sf::Text(txtInstructions1, font);
		text1.setCharacterSize(30);
		text1.setStyle(sf::Text::Bold);

		// Calculate the position to center the text
		textRect1 = text1.getLocalBounds();
		text1.setOrigin(textRect1.left + textRect1.width / 2.0f, textRect1.top + textRect1.height / 2.0f);
		text1.setPosition(sf::Vector2f(window->getSize().x / 2.0f, window->getSize().y / 2.0f));

		text1.setFillColor(sf::Color::White);
		text1.setPosition(680, 100);
		window->draw(text1);

		// Create a text
		text1 = sf::Text(txtInstructions2, font);
		text1.setCharacterSize(30);
		text1.setStyle(sf::Text::Bold);

		// Calculate the position to center the text
		textRect1 = text1.getLocalBounds();
		text1.setOrigin(textRect1.left + textRect1.width / 2.0f, textRect1.top + textRect1.height / 2.0f);
		text1.setPosition(sf::Vector2f(window->getSize().x / 2.0f, window->getSize().y / 2.0f));

		text1.setFillColor(sf::Color::White);
		text1.setPosition(680, 160);
		window->draw(text1);

		// Create a text
		text1 = sf::Text(txtInstructions3, font);
		text1.setCharacterSize(30);
		text1.setStyle(sf::Text::Bold);

		// Calculate the position to center the text
		textRect1 = text1.getLocalBounds();
		text1.setOrigin(textRect1.left + textRect1.width / 2.0f, textRect1.top + textRect1.height / 2.0f);
		text1.setPosition(sf::Vector2f(window->getSize().x / 2.0f, window->getSize().y / 2.0f));

		text1.setFillColor(sf::Color::White);
		text1.setPosition(680, 200);
		window->draw(text1);

		// Create a text
		text1 = sf::Text(txtInstructions4, font);
		text1.setCharacterSize(30);
		text1.setStyle(sf::Text::Bold);

		// Calculate the position to center the text
		textRect1 = text1.getLocalBounds();
		text1.setOrigin(textRect1.left + textRect1.width / 2.0f, textRect1.top + textRect1.height / 2.0f);
		text1.setPosition(sf::Vector2f(window->getSize().x / 2.0f, window->getSize().y / 2.0f));

		text1.setFillColor(sf::Color::White);
		text1.setPosition(680, 230);
		window->draw(text1);
	}
}
