#include "pch.h"
#include "BurgerTime.h"

#include "PeakAEngine/SceneManager.h"
#include "PeakAEngine/Logger.h"
#include "Achievements.h"
#include "Level.h"
#include "Prefabs.h"


BurgerTime::~BurgerTime()
{
	delete m_pLevel;
}

void BurgerTime::LoadGame()
{
	AchievementSystem::GetInstance().Initialize(m_UseSteam);

	Logger::LogInfo("Started Creating Scene Objects...");
	auto& scene = SceneManager::GetInstance().CreateScene("BurgerTime");

	m_pLevel = new Level();
	m_pLevel->Initialize(&scene);

	// Enemies


	// Player
	CreatePeterPepper(&scene, { BurgerTime::WindowWidth() / 2,BurgerTime::WindowHeight() / 2 });
}
