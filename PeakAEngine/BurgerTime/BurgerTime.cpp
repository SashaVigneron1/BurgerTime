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
#include "PeakAEngine/Scene.h"
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

	#pragma region MainMenu
	auto& mainMenu = SceneManager::GetInstance().CreateScene("MainMenu");
	mainMenu.EnableOnGUI(false);

	CreateMainMenu(&mainMenu, this);

	#pragma endregion

	#pragma region Level2Solo
	auto& level2Solo = SceneManager::GetInstance().CreateScene("Level2_Solo");
	level2Solo.EnableOnGUI(true);

	// UI
	CreateUI(&level2Solo);

	// Level
	m_pLevel = new Level(true, "Resources/Levels/level2.json");
	m_pLevel->Initialize(&level2Solo);

	// Enemies

	// Player
	CreatePeterPepper(&level2Solo, { BurgerTime::WindowWidth() / 2,BurgerTime::WindowHeight() / 2 });
	#pragma endregion

	#pragma region Level2Coop
	auto& level2Coop = SceneManager::GetInstance().CreateScene("Level2_Coop");
	level2Coop.EnableOnGUI(true);

	m_pLevel = new Level(true, "Resources/Levels/level2.json");
	m_pLevel->Initialize(&level2Coop);

	// Enemies


	// Players
	CreatePeterPepper(&level2Coop, { BurgerTime::WindowWidth() / 2,BurgerTime::WindowHeight() / 2 });
	#pragma endregion

	// Sound Test
	/*auto& serviceLocator = ServiceLocator::GetInstance();
	serviceLocator.RegisterSoundSystem(new Logged_SoundSystem());
	int id = serviceLocator.GetSoundSystem()->AddClip("Resources/test.wav");
	serviceLocator.GetSoundSystem()->Play(id);*/
}
