#include "PeakAEnginePCH.h"
#include "Time.h"

float Time::deltaTime = 0.f;
float Time::elapsedTime = 0.f;
float Time::fixedTime = 0.f;

void Time::CalculateTime()
{
	if (!hasStarted) { lastTime = std::chrono::high_resolution_clock::now(); hasStarted = true; }

	const auto currTime = std::chrono::high_resolution_clock::now();
	deltaTime = std::chrono::duration<float>(currTime - lastTime).count();
	lastTime = currTime;
	elapsedTime += deltaTime;
}
