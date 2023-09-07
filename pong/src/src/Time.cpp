#include "Time.h"

Time::Time()
{
}

void Time::Update()
{
	if (curDeltaTime.getElapsedTime() > maxDeltaTime)
	{
		deltaTime = maxDeltaTime;
	}
	else
	{
		deltaTime = curDeltaTime.getElapsedTime();
	}

	deltaTime = deltaTime * timeScale;

	time += deltaTime;

	curDeltaTime.restart();
}

void Time::Stop()
{
	timeScale = 0.f;
	isStopped = true;
}

void Time::Start()
{
	timeScale = 1.f;
	isStopped = false;
}
