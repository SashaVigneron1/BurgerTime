#pragma once
#include <chrono>

#include "SingleInstance.h"

class Time final : public SingleInstance<Time>
{
public:
	void CalculateTime();

	void SetFixedTime(float fixedTimeStep) { fixedTime = fixedTimeStep; }

	static float FixedTime() { return fixedTime; }
	static float ElapsedTime() { return elapsedTime; }
	static float DeltaTime() { return deltaTime; }
private:
	bool hasStarted = false;
	static float elapsedTime;
	static float deltaTime;
	static float fixedTime;

	std::chrono::steady_clock::time_point lastTime;
};
