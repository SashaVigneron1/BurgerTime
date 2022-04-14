#pragma once

#include <unordered_map>

#include "PeakAEngine/BaseObserver.h"
#include "PeakAEngine/Singleton.h"

enum class Achievement
{
	FiveHundredPoints = 0,
	LAST_ELEMENT = 1,
};

struct AchievementInfo
{
	int id = 0;
	std::string steamName = "";
	bool isUnlocked = false;
};

class AchievementSystem final : public Singleton<AchievementSystem>, public BaseObserver
{
public:
	virtual ~AchievementSystem() override;


	void Initialize(bool useSteam = false);

	void Notify(Component* pComponent, Event event) override;

private:
	bool m_UseSteam{false};

	bool RequestUserStats();
	void UnlockAchievement(Achievement achievement);

	std::unordered_map<Achievement, AchievementInfo*> m_pAchievements;

};

