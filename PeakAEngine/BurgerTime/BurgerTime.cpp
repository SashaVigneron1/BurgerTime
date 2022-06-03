#include "pch.h"
#include "BurgerTime.h"

#include <thread>

#include "PeakAEngine/SceneManager.h"
#include "PeakAEngine/Logger.h"
#include "Achievements.h"
#include "Level.h"
#include "Prefabs.h"

#include "RenderLayers.h"
#include "PeakAEngine/Renderer.h"
#include "PeakAEngine/ServiceLocator.h"

BurgerTime::~BurgerTime()
{
	delete m_pLevel;
}

void BurgerTime::LoadGame()
{
	for (int i{}; i < (int)Layer::SIZE; ++i)
		RENDERER.AddLayer();

	AchievementSystem::GetInstance().Initialize(m_UseSteam);

	Logger::LogInfo("Started Creating Scene Objects...");
	auto& scene = SceneManager::GetInstance().CreateScene("BurgerTime");

	m_pLevel = new Level(true, "Resources/level2.json");
	m_pLevel->Initialize(&scene);

	// Enemies

	// Player
	CreatePeterPepper(&scene, { BurgerTime::WindowWidth() / 2,BurgerTime::WindowHeight() / 2 });

	// Sound Test
	/*auto& serviceLocator = ServiceLocator::GetInstance();
	serviceLocator.RegisterSoundSystem(new Logged_SoundSystem());
	int id = serviceLocator.GetSoundSystem()->AddClip("Resources/test.wav");
	serviceLocator.GetSoundSystem()->Play(id);*/
}
