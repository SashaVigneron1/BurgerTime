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

	#pragma region Level1Solo
	auto& level1Solo = SceneManager::GetInstance().CreateScene("Level1_Solo");
	level1Solo.EnableOnGUI(true);

	// UI
	CreateUI(&level1Solo, 1);

	// Level
	m_pLevel = new Level(false, true, "Resources/Levels/level2.json");
	m_pLevel->Initialize(&level1Solo);

	// Enemies

	// Player
	CreatePeterPepper(&level1Solo, { BurgerTime::WindowWidth() / 2,BurgerTime::WindowHeight() / 2 });
	#pragma endregion

	#pragma region Level2Solo
	auto& level2Solo = SceneManager::GetInstance().CreateScene("Level2_Solo");
	level2Solo.EnableOnGUI(true);

	// UI
	CreateUI(&level2Solo, 2);

	// Level
	m_pLevel = new Level(false, true, "Resources/Levels/level2.json");
	m_pLevel->Initialize(&level2Solo);

	// Enemies

	// Player
	CreatePeterPepper(&level2Solo, { BurgerTime::WindowWidth() / 2,BurgerTime::WindowHeight() / 2 });
	#pragma endregion

	#pragma region Level3Solo
	auto& level3Solo = SceneManager::GetInstance().CreateScene("Level3_Solo");
	level3Solo.EnableOnGUI(true);

	// UI
	CreateUI(&level3Solo, 3);

	// Level
	m_pLevel = new Level(true, true, "Resources/Levels/level2.json");
	m_pLevel->Initialize(&level3Solo);

	// Enemies

	// Player
	CreatePeterPepper(&level3Solo, { BurgerTime::WindowWidth() / 2,BurgerTime::WindowHeight() / 2 });
	#pragma endregion

	#pragma region Level1Coop
	auto& level1Coop = SceneManager::GetInstance().CreateScene("Level1_Coop");
	level1Coop.EnableOnGUI(true);

	// UI
	CreateUI(&level1Coop, 1);

	m_pLevel = new Level(false, true, "Resources/Levels/level2.json");
	m_pLevel->Initialize(&level1Coop);

	// Enemies


	// Players
	CreatePeterPepper(&level1Coop, { BurgerTime::WindowWidth() / 2,BurgerTime::WindowHeight() / 2 });
	CreatePeterPepper(&level1Coop, { BurgerTime::WindowWidth() / 2,BurgerTime::WindowHeight() / 2 }, 0);
#pragma endregion

	#pragma region Level2Coop
	auto& level2Coop = SceneManager::GetInstance().CreateScene("Level2_Coop");
	level2Coop.EnableOnGUI(true);

	// UI
	CreateUI(&level2Coop, 2);

	m_pLevel = new Level(false, true, "Resources/Levels/level2.json");
	m_pLevel->Initialize(&level2Coop);

	// Enemies


	// Players
	CreatePeterPepper(&level2Coop, { BurgerTime::WindowWidth() / 2,BurgerTime::WindowHeight() / 2 });
	CreatePeterPepper(&level2Coop, { BurgerTime::WindowWidth() / 2,BurgerTime::WindowHeight() / 2 }, 0);
	#pragma endregion

	#pragma region Level3Coop
	auto& level3Coop = SceneManager::GetInstance().CreateScene("Level3_Coop");
	level3Coop.EnableOnGUI(true);

	// UI
	CreateUI(&level3Coop, 3);

	m_pLevel = new Level(true, true, "Resources/Levels/level2.json");
	m_pLevel->Initialize(&level3Coop);

	// Enemies

	// Players
	CreatePeterPepper(&level3Coop, { BurgerTime::WindowWidth() / 2,BurgerTime::WindowHeight() / 2 });
	CreatePeterPepper(&level3Coop, { BurgerTime::WindowWidth() / 2,BurgerTime::WindowHeight() / 2 }, 0);
#pragma endregion

	// Sound Test
	auto& serviceLocator = ServiceLocator::GetInstance();
	serviceLocator.RegisterSoundSystem(new Logged_SoundSystem());
	int id = serviceLocator.GetSoundSystem()->AddClip("Resources/Sounds/BackgroundMusic.wav", -1);
	serviceLocator.GetSoundSystem()->Play(id);
}
