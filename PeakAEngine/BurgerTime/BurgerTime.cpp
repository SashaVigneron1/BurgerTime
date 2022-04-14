#include "pch.h"
#include "BurgerTime.h"

#include "Achievements.h"
#include "PeakAEngine/SceneManager.h"
#include "PeakAEngine/Scene.h"

#include "Prefabs.h"
#include "PeakAEngine/Logger.h"

void BurgerTime::LoadGame() const
{
	AchievementSystem::GetInstance().Initialize(m_UseSteam);

	Logger::LogInfo("Started Creating Scene Objects...");
	auto& scene = SceneManager::GetInstance().CreateScene("BurgerTime");

	scene.Add(CreatePeterPepper(&scene, { BurgerTime::m_WindowWidth/2,BurgerTime::m_WindowHeight/2 }));
}
