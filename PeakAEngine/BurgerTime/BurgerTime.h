#pragma once
#include <vector>

#include "PeakAEngine/PeakAEngine.h"

class Level;

class BurgerTime final : public PeakAEngine
{
public:
	BurgerTime(float windowWidth, float windowHeight)
		: BurgerTime(windowWidth, windowHeight, false)
	{}
	BurgerTime(float windowWidth, float windowHeight, bool useSteam)
		: PeakAEngine{windowWidth, windowHeight, useSteam}
	{}

	virtual ~BurgerTime() override;

protected:
	void LoadGame() override;

	std::vector<Level*> m_pLevels;
};

