#include "pch.h"
#include "Achievements.h"

#include "3rdParty/steamworks/public/steam/isteamuserstats.h"

#include "Events.h"

AchievementSystem::~AchievementSystem()
{
	for (const auto& [achievement, info] : m_pAchievements)
	{
		delete info;
	}
}

void AchievementSystem::Initialize(bool useSteam)
{
	m_UseSteam = useSteam;

	// Achievements
	m_pAchievements[Achievement::FiveHundredPoints] = new AchievementInfo{ 0, "ACH_TRAVEL_FAR_SINGLE", false };

	if (m_UseSteam)
	{
		if (RequestUserStats())
		{
			SteamUserStats()->RequestCurrentStats();

			// Get Already Unlocked Achievements
			for (int i{ 0 }; i < (int)Achievement::LAST_ELEMENT; ++i)
			{
				bool isUnlocked = false;
				SteamUserStats()->GetAchievement(m_pAchievements[(Achievement)i]->steamName.c_str(), &isUnlocked);
				m_pAchievements[(Achievement)i]->isUnlocked = isUnlocked;
			}
		}
		else
		{
			std::cerr << "[Achievements.cpp] Something went wrong receiving the User Stats" << std::endl;
		}
	}
}

bool AchievementSystem::RequestUserStats()
{
	if (m_UseSteam)
		return SteamUserStats()->RequestCurrentStats();

	return false;
}

void AchievementSystem::Notify(Component* /*pComponent*/, Event event)
{
	switch (event)
	{
	case Event::OnBurgerFell:
		break;
	case Event::OnPlayerDied:
		UnlockAchievement(Achievement::FiveHundredPoints);
		break;
	}
}

void AchievementSystem::UnlockAchievement(Achievement achievement)
{
	switch (achievement)
	{
	case Achievement::FiveHundredPoints:
		if (!m_pAchievements[Achievement::FiveHundredPoints]->isUnlocked)
		{
			if (m_UseSteam)
				SteamUserStats()->SetAchievement(m_pAchievements[Achievement::FiveHundredPoints]->steamName.c_str());

			m_pAchievements[Achievement::FiveHundredPoints]->isUnlocked = true;

			std::cout << "RECEIVED ACHIEVEMENT: FiveHundredPoints\n";
		}
		break;
	}
	if (m_UseSteam)
		SteamUserStats()->StoreStats();
}
