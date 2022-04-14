#include "pch.h"
#include "BurgerTime.h"

#include <functional>

#include "Achievements.h"
#include "PeakAEngine/SceneManager.h"
#include "PeakAEngine/ResourceManager.h"

#include "PeakAEngine/GameObject.h"
#include "PeakAEngine/InputManager.h"
#include "LivesCounter.h"
#include "PeterPepper.h"
#include "PeakAEngine/Scene.h"

#include "PeakAEngine/RenderComponent.h"
#include "ScoreCounter.h"
#include "PeakAEngine/Text.h"

#include "Commands.h"
#include "PeakAEngine/Logger.h"
#include "PeakAEngine/PhysicsComponent.h"
#include "PeakAEngine/SpriteRenderer.h"

void BurgerTime::LoadGame() const
{
	AchievementSystem::GetInstance().Initialize(m_UseSteam);

	Logger::LogInfo("Started Creating Scene Objects...");
	auto& scene = SceneManager::GetInstance().CreateScene("BurgerTime");

	auto go = new GameObject(&scene);

#pragma region Player1
	// Peter Pepper Object
	// Info
	float size = 100;

	go = new GameObject(&scene, glm::vec3(80, 200, 0));
	SpriteRenderer* pSpriteRenderer = new SpriteRenderer(go);
	pSpriteRenderer->AddSprite("Walking", new  Sprite("PeterPepper_Walking.png",
		{
				SpriteRow{Direction::FacingCamera, 0},
				SpriteRow{Direction::FacingLeft, 1},
				SpriteRow{Direction::FacingRight, 1, true},
				SpriteRow{Direction::FacingAwayFromCamera, 2},
		},
		3, 0.2f, size, go));
	pSpriteRenderer->AddSprite("Idle", new  Sprite("PeterPepper_Idle.png",
		{
				SpriteRow{Direction::FacingCamera, 0}
		},
		1, 0.2f, size, go));
	go->AddComponent(pSpriteRenderer);

	PeterPepper* pPeterPepper = new PeterPepper(pSpriteRenderer, go);
	auto physics = new PhysicsComponent(go);
	go->AddComponent(physics);
	physics->AddBoxCollider(size, size, true);
	physics->OnTriggerEnter = std::bind(&PeterPepper::OnTriggerEnter, pPeterPepper, std::placeholders::_1);
	physics->OnTriggerExit = std::bind(&PeterPepper::OnTriggerExit, pPeterPepper, std::placeholders::_1);

	pPeterPepper->AddObserver(&AchievementSystem::GetInstance());
	go->AddComponent(pPeterPepper);
	PeterPepper_Die* pPeterPepperDieCommand = new PeterPepper_Die(pPeterPepper);
	PeterPepper_KillEnemy* pPeterPepperKillEnemyCommand = new PeterPepper_KillEnemy(pPeterPepper);
	InputManager::GetInstance().AddCommand('z', pPeterPepperDieCommand);
	InputManager::GetInstance().AddCommand('d', pPeterPepperKillEnemyCommand);

	scene.Add(go);

	#pragma endregion

#pragma region TestObj
	size = 50;

	go = new GameObject(&scene, glm::vec3(300, 200, 0));
	pSpriteRenderer = new SpriteRenderer(go);
	pSpriteRenderer->AddSprite("Walking", new  Sprite("PeterPepper_Walking.png",
		{
				SpriteRow{Direction::FacingCamera, 0},
				SpriteRow{Direction::FacingLeft, 1},
				SpriteRow{Direction::FacingRight, 1, true},
				SpriteRow{Direction::FacingAwayFromCamera, 2},
		},
		3, 0.2f, size, go));
	pSpriteRenderer->AddSprite("Idle", new  Sprite("PeterPepper_Idle.png",
		{
				SpriteRow{Direction::FacingCamera, 0}
		},
		1, 0.2f, size, go));
	go->AddComponent(pSpriteRenderer);
	physics = new PhysicsComponent(go);
	physics->AddBoxCollider(size, size, true);
	
	go->AddComponent(physics);
	scene.Add(go);
#pragma endregion
}
