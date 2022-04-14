#pragma once
#include "PeakAEngine/PeakAEngine.h"

class BurgerTime final : public PeakAEngine
{
public:
	BurgerTime(float windowWidth, float windowHeight)
		: BurgerTime(windowWidth, windowHeight, false)
	{}
	BurgerTime(float windowWidth, float windowHeight, bool useSteam)
		: PeakAEngine{windowWidth, windowHeight, useSteam}
	{}

protected:
	void LoadGame() const override;
};

