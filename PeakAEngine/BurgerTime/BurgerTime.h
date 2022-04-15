#pragma once
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
		, m_pLevel{nullptr}
	{}

	virtual ~BurgerTime() override;

	Level* m_pLevel;
protected:
	void LoadGame() override;

};

