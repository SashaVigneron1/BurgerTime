#pragma once
#include "PeakAEngine/PeakAEngine.h"

class BurgerTime final : public PeakAEngine
{
public:
	BurgerTime()
		: BurgerTime(false)
	{}
	BurgerTime(bool useSteam)
		: PeakAEngine{useSteam}
	{}

protected:
	void LoadGame() const override;
};

