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
#include "PeakAEngine/SpriteRenderer.h"

void BurgerTime::LoadGame() const
{
	AchievementSystem::GetInstance().Initialize(m_UseSteam);

	Logger::LogInfo("Started Creating Scene Objects...");
	auto& scene = SceneManager::GetInstance().CreateScene("BurgerTime");

	auto go = new GameObject();
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

#pragma region Player1
	// LivesCounter Object
	go = new GameObject(glm::vec3(20, 200, 0));
	auto pRenderComponent = new RenderComponent("logo.png", go);
	go->AddComponent(pRenderComponent);
	auto pTextComponent = new Text("Lives: 3", glm::u8vec3(255, 0, 255), font, go, pRenderComponent);
	go->AddComponent(pTextComponent);
	LivesCounter* pLivesCounter = new LivesCounter(go, pTextComponent);
	go->AddComponent(pLivesCounter);
	scene.Add(go);

	// ScoreCounter Object
	go = new GameObject(glm::vec3(20, 240, 0));
	pRenderComponent = new RenderComponent("logo.png", go);
	go->AddComponent(pRenderComponent);
	pTextComponent = new Text("Score: 0", glm::u8vec3(255, 0, 255), font, go, pRenderComponent);
	go->AddComponent(pTextComponent);
	ScoreCounter* pScoreCounter = new ScoreCounter(go, pTextComponent);
	go->AddComponent(pScoreCounter);
	scene.Add(go);

	// Peter Pepper Object
	go = new GameObject(glm::vec3(80, 200, 0));
	SpriteRenderer* pSpriteRenderer = new SpriteRenderer(go);

	pSpriteRenderer->AddSprite("Walking", new  Sprite("PeterPepper_Walking.png",
		{
				SpriteRow{Direction::FacingCamera, 0},
				SpriteRow{Direction::FacingLeft, 1},
				SpriteRow{Direction::FacingRight, 1, true},
				SpriteRow{Direction::FacingAwayFromCamera, 2},
		},
		3, 0.2f, 10, go));
	pSpriteRenderer->AddSprite("Idle", new  Sprite("PeterPepper_Idle.png",
		{
				SpriteRow{Direction::FacingCamera, 0}
		},
		1, 0.2f, 10, go));
	go->AddComponent(pSpriteRenderer);

	PeterPepper* pPeterPepper = new PeterPepper(pSpriteRenderer, go);
	pPeterPepper->AddObserver(pLivesCounter);
	pPeterPepper->AddObserver(pScoreCounter);
	pPeterPepper->AddObserver(&AchievementSystem::GetInstance());
	go->AddComponent(pPeterPepper);
	PeterPepper_Die* pPeterPepperDieCommand = new PeterPepper_Die(pPeterPepper);
	PeterPepper_KillEnemy* pPeterPepperKillEnemyCommand = new PeterPepper_KillEnemy(pPeterPepper);
	InputManager::GetInstance().AddCommand('z', pPeterPepperDieCommand);
	InputManager::GetInstance().AddCommand('d', pPeterPepperKillEnemyCommand);

	scene.Add(go);

	/*auto go2 = new GameObject(glm::vec3(0, 0, 0));
	pSprite = new Sprite("PeterPepper_Walking.png",
		{
				SpriteRow{Direction::FacingCamera, 0},
				SpriteRow{Direction::FacingLeft, 1},
				SpriteRow{Direction::FacingRight, 1, true},
				SpriteRow{Direction::FacingAwayFromCamera, 2},
		},
		3, 0.2f, 5, go2);
	go2->AddComponent(pSprite);
	go2->AddComponent(new PeterPepperTest(go2));
	go2->SetParent(go);*/

	#pragma endregion

}
