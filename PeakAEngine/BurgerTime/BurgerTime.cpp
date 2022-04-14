#include "pch.h"
#include "BurgerTime.h"

#include "Achievements.h"
#include "Ladder.h"
#include "PeakAEngine/SceneManager.h"
#include "PeakAEngine/Scene.h"

#include "Prefabs.h"
#include "PeakAEngine/GameObject.h"
#include "PeakAEngine/Logger.h"
#include "PeakAEngine/PhysicsComponent.h"
#include "PeakAEngine/SpriteRenderer.h"

void BurgerTime::LoadGame() const
{
	AchievementSystem::GetInstance().Initialize(m_UseSteam);

	Logger::LogInfo("Started Creating Scene Objects...");
	auto& scene = SceneManager::GetInstance().CreateScene("BurgerTime");

	// Level
	CreateLadderCollection(&scene, 5, { BurgerTime::m_WindowWidth / 2,BurgerTime::m_WindowHeight / 2 });

	// Enemies

	// Player
	CreatePeterPepper(&scene, { BurgerTime::m_WindowWidth / 2,BurgerTime::m_WindowHeight / 2 });
}
