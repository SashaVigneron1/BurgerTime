#include "pch.h"
#include "Prefabs.h"

#include <functional>

#include "Achievements.h"
#include "BurgerCatcher.h"
#include "BurgerTime.h"


#include "PeakAEngine/GameObject.h"

#include "PeakAEngine/SpriteRenderer.h"
#include "PeakAEngine/PhysicsComponent.h"

#include "PeterPepper.h"
#include "Commands.h"
#include "HighScoreCounter.h"
#include "Ladder.h"
#include "LevelCounter.h"
#include "LivesCounter.h"
#include "PepperCounter.h"
#include "Platform.h"
#include "RenderLayers.h"
#include "ScoreCounter.h"
#include "PeakAEngine/Button.h"
#include "PeakAEngine/RenderComponent.h"
#include "PeakAEngine/ResourceManager.h"
#include "PeakAEngine/Scene.h"
#include "PeakAEngine/Text.h"


void CreatePeterPepper(Scene* pScene, const glm::vec2& position)
{
	auto go = pScene->Add(new GameObject(pScene, { position.x, position.y, 0 }));
	//// PETER PEPPER
	// Info
	const float size = 35;
	const float frameSec = 0.05f;

	// Sprite
	SpriteRenderer* pSpriteRenderer = go->AddComponent(new SpriteRenderer(go));
	pSpriteRenderer->AddSprite("Walking", new  Sprite("Character/PeterPepper_Walking.png",
		{
				SpriteRow{Direction::FacingCamera, 0},
				SpriteRow{Direction::FacingLeft, 1},
				SpriteRow{Direction::FacingRight, 1, true},
				SpriteRow{Direction::FacingAwayFromCamera, 2},
		},
		3, frameSec, size, go, (int)Layer::Player));
	pSpriteRenderer->AddSprite("Idle", new  Sprite("Character/PeterPepper_Idle.png",
		{
				SpriteRow{Direction::FacingCamera, 0}
		},
		1, frameSec, size, go, (int)Layer::Player));

	// Physics
	auto physics = go->AddComponent(new PhysicsComponent(go));
	physics->AddBoxCollider(size, size / 4, true, { 0,size / 2 - size / 8 });
	physics->SetDebugColor({ 1,1,0,0.3f });

	auto pepperCounter = pScene->FindObjectOfType<PepperCounter>();

	auto pPeterPepper = go->AddComponent(new PeterPepper(pepperCounter, pSpriteRenderer, physics, go));
	physics->OnTriggerEnter = std::bind(&PeterPepper::OnTriggerEnter, pPeterPepper, std::placeholders::_1);
	physics->OnTriggerExit = std::bind(&PeterPepper::OnTriggerExit, pPeterPepper, std::placeholders::_1);

	// Observers
	pPeterPepper->AddObserver(&AchievementSystem::GetInstance());
	pPeterPepper->AddObserver(pepperCounter);

	// Commands
	//ToDo: Fix Deletion
	/*auto pPeterPepperDieCommand = new PeterPepper_Die(pPeterPepper);
	auto* pPeterPepperKillEnemyCommand = new PeterPepper_KillEnemy(pPeterPepper);*/
	/*go->AddCommand('z', pPeterPepperDieCommand);
	go->AddCommand('d', pPeterPepperKillEnemyCommand);*/

	go->AddTag("PeterPepper");
}
void CreateLadder(Scene* pScene, float tileSize, const glm::vec2& position)
{
	// GameObject
	auto go = pScene->Add(new GameObject(pScene, { position.x, position.y + tileSize / 2, 0 }));
	go->AddComponent(new Ladder(go));

	// Physics
	auto physics = go->AddComponent(new PhysicsComponent(go));
	physics->AddBoxCollider(tileSize, tileSize, true);
	physics->SetDebugColor({ 0,1,0,0.3f });

	// Sprite
	auto pSpriteRenderer = go->AddComponent(new SpriteRenderer(go));
	pSpriteRenderer->AddSprite("Idle", new  Sprite("Environment/Ladder.png",
		{
				SpriteRow{Direction::FacingCamera, 0}
		},
		1, 1.f, tileSize, go, (int)Layer::Ladders));
	go->AddTag("Ladder");
}
void CreatePlatform(Scene* pScene, PlatformType type, float tileSize, const glm::vec2& position)
{
	// GameObject
	auto go = pScene->Add(new GameObject(pScene, { position.x, position.y + tileSize / 2, 0 }));
	go->AddTag("Platform");
	go->AddComponent(new Platform(go));

	// Physics
	auto physics = go->AddComponent(new PhysicsComponent(go));
	physics->AddBoxCollider(tileSize, tileSize / 4, true, { 0,-tileSize / 2 });
	physics->SetDebugColor({ 0,1,1,0.3f });

	// Sprite
	std::string spriteName = (type == PlatformType::normal) ? "Environment/Platform.png" : "Environment/Platform_Coupled.png";
	auto pSpriteRenderer = go->AddComponent(new SpriteRenderer(go));
	pSpriteRenderer->AddSprite("Idle", new  Sprite(spriteName,
		{
				SpriteRow{Direction::FacingCamera, 0}
		},
		1, 1.f, tileSize, go, (int)Layer::Platforms));

}

void CreateBurgerIngredient(Scene* pScene, BurgerPieceType type, float tileSize, const glm::vec2& position)
{
	auto go = pScene->Add(new GameObject(pScene, { position.x, position.y, 0 }));

	auto physics = go->AddComponent(new PhysicsComponent(go));
	physics->AddBoxCollider(tileSize * 2.5f, tileSize, true, { tileSize - 10,0 });
	physics->SetDebugColor({ 0,0,1,0.3f });

	go->AddComponent(new BurgerPiece(type, tileSize, physics, go));

	go->AddTag("BurgerIngredient");
}

BurgerCatcher* CreateBurgerCatcher(Scene* pScene, float tileSize, const glm::vec2& position)
{
	auto go = pScene->Add(new GameObject(pScene, { position.x + 20, position.y, 0 }));

	auto physics = go->AddComponent(new PhysicsComponent(go));
	physics->AddBoxCollider(tileSize * 2.5f, tileSize * 2.5f, true, { tileSize - 20,0 });
	physics->SetDebugColor({ 1,1,0,0.3f });

	auto burgerCatcher = go->AddComponent(new BurgerCatcher(go));
	physics->OnTriggerEnter = std::bind(&BurgerCatcher::OnTriggerEnter, burgerCatcher, std::placeholders::_1);
	physics->OnTriggerExit = std::bind(&BurgerCatcher::OnTriggerExit, burgerCatcher, std::placeholders::_1);

	auto pSpriteRenderer = go->AddComponent(new SpriteRenderer(go));
	pSpriteRenderer->AddSprite("Idle", new  Sprite("Environment/BurgerCatcher.png",
		{
				SpriteRow{Direction::FacingCamera, 0}
		},
		1, 1.f, tileSize * 2.5f, go, (int)Layer::BurgerCatcher));

	go->AddTag("BurgerCatcher");

	return burgerCatcher;
}

void CreateMainMenu(Scene* pScene, BurgerTime* pGame)
{
	glm::vec2 screenCentre{ BurgerTime::WindowWidth() / 2, BurgerTime::WindowHeight() / 2 };

	// Create Logo
	auto go = pScene->Add(new GameObject(pScene, { screenCentre.x, screenCentre.y - BurgerTime::WindowHeight() / 4, 0 }));
	auto spriteRenderer = go->AddComponent(new SpriteRenderer(go));
	spriteRenderer->AddSprite("Idle", new  Sprite("UI/Logo.png",
		{
				SpriteRow{Direction::FacingCamera, 0}
		},
		1, 1.f, BurgerTime::WindowWidth() / 1.5f, go, (int)Layer::UI));

	// Create Play Solo Button
	glm::vec2 buttonPos = { screenCentre.x, screenCentre.y };
	constexpr float buttonOffset{ 140 };

	go = pScene->Add(new GameObject(pScene, { buttonPos.x, buttonPos.y, 0 }));
	spriteRenderer = go->AddComponent(new SpriteRenderer(go));
	spriteRenderer->AddSprite("Idle", new  Sprite("UI/PlaySolo_Idle.png",
		{
				SpriteRow{Direction::FacingCamera, 0}
		},
		1, 1.f, BurgerTime::WindowWidth() / 2, go, (int)Layer::UI));
	spriteRenderer->AddSprite("Highlighted", new  Sprite("UI/PlaySolo_Highlighted.png",
		{
				SpriteRow{Direction::FacingCamera, 0}
		},
		1, 1.f, BurgerTime::WindowWidth() / 2, go, (int)Layer::UI));
	spriteRenderer->AddSprite("Pressed", new  Sprite("UI/PlaySolo_Pressed.png",
		{
				SpriteRow{Direction::FacingCamera, 0}
		},
		1, 1.f, BurgerTime::WindowWidth() / 2, go, (int)Layer::UI));
	go->AddComponent(new Button(Rectf{ 0,0,BurgerTime::WindowWidth() / 2,100 }, spriteRenderer, "Idle", "Highlighted", "Pressed",
		[]
		{
			SceneManager::GetInstance().LoadScene("Level2_Solo");
		}
		, go));

	// Create Play Coop Button
	buttonPos.y += buttonOffset;
	go = pScene->Add(new GameObject(pScene, { buttonPos.x, buttonPos.y, 0 }));
	spriteRenderer = go->AddComponent(new SpriteRenderer(go));
	spriteRenderer->AddSprite("Idle", new  Sprite("UI/PlayCoop_Idle.png",
		{
				SpriteRow{Direction::FacingCamera, 0}
		},
		1, 1.f, BurgerTime::WindowWidth() / 2, go, (int)Layer::UI));
	spriteRenderer->AddSprite("Highlighted", new  Sprite("UI/PlayCoop_Highlighted.png",
		{
				SpriteRow{Direction::FacingCamera, 0}
		},
		1, 1.f, BurgerTime::WindowWidth() / 2, go, (int)Layer::UI));
	spriteRenderer->AddSprite("Pressed", new  Sprite("UI/PlayCoop_Pressed.png",
		{
				SpriteRow{Direction::FacingCamera, 0}
		},
		1, 1.f, BurgerTime::WindowWidth() / 2, go, (int)Layer::UI));
	go->AddComponent(new Button(Rectf{ 0,0,BurgerTime::WindowWidth() / 2,100 }, spriteRenderer, "Idle", "Highlighted", "Pressed",
		[]
		{
			SceneManager::GetInstance().LoadScene("Level2_Coop");
		}
		, go));

	// Create Versus Button (not interactible)


	// Create Quit Button
	#pragma region QuitButton
	buttonPos.y += buttonOffset;
	go = pScene->Add(new GameObject(pScene, { buttonPos.x, buttonPos.y, 0 }));
	spriteRenderer = go->AddComponent(new SpriteRenderer(go));
	spriteRenderer->AddSprite("Idle", new  Sprite("UI/Quit_Idle.png",
		{
				SpriteRow{Direction::FacingCamera, 0}
		},
		1, 1.f, BurgerTime::WindowWidth() / 2, go, (int)Layer::UI));
	spriteRenderer->AddSprite("Highlighted", new  Sprite("UI/Quit_Highlighted.png",
		{
				SpriteRow{Direction::FacingCamera, 0}
		},
		1, 1.f, BurgerTime::WindowWidth() / 2, go, (int)Layer::UI));
	spriteRenderer->AddSprite("Pressed", new  Sprite("UI/Quit_Pressed.png",
		{
				SpriteRow{Direction::FacingCamera, 0}
		},
		1, 1.f, BurgerTime::WindowWidth() / 2, go, (int)Layer::UI));
	go->AddComponent(new Button(Rectf{ 0,0,BurgerTime::WindowWidth() / 2,100 }, spriteRenderer, "Idle", "Highlighted", "Pressed",
		[pGame]
		{
			pGame->Quit();
		}
		, go));
	#pragma endregion
}

void CreateUI(Scene* pScene)
{
	auto font = ResourceManager::GetInstance().LoadFont("UI/Cyber11.ttf", 45);

	// Create Current Score 
	auto go = pScene->Add(new GameObject(pScene, { 10,10, 0 }));
	RenderComponent* pRenderComponent = new RenderComponent("", go);
	go->AddComponent(pRenderComponent);
	go->AddComponent(new Text("1UP", glm::u8vec3(255, 0, 0), font, go, pRenderComponent));

	go = pScene->Add(new GameObject(pScene, { 10,55, 0 }));
	pRenderComponent = new RenderComponent("", go);
	go->AddComponent(pRenderComponent);
	auto textComponent = go->AddComponent(new Text("2800", glm::u8vec3(255, 255, 255), font, go, pRenderComponent));
	go->AddComponent(new ScoreCounter(go, textComponent));

	// Create High Score
	go = pScene->Add(new GameObject(pScene, { 150,10, 0 }));
	pRenderComponent = new RenderComponent("", go);
	go->AddComponent(pRenderComponent);
	go->AddComponent(new Text("HI-SCORE", glm::u8vec3(255, 0, 0), font, go, pRenderComponent));

	go = pScene->Add(new GameObject(pScene, { 150,55, 0 }));
	pRenderComponent = new RenderComponent("", go);
	go->AddComponent(pRenderComponent);
	textComponent = go->AddComponent(new Text("28000", glm::u8vec3(255, 255, 255), font, go, pRenderComponent));
	go->AddComponent(new HighScoreCounter(go, textComponent));
	// Read & Write To File

	// Create Peppers
	go = pScene->Add(new GameObject(pScene, { BurgerTime::WindowWidth(),10, 0 }));
	pRenderComponent = new RenderComponent("", go, { 1,0 });
	go->AddComponent(pRenderComponent);
	go->AddComponent(new Text("PEPPER", glm::u8vec3(0, 255, 0), font, go, pRenderComponent));

	go = pScene->Add(new GameObject(pScene, { BurgerTime::WindowWidth(),55, 0 }));
	pRenderComponent = new RenderComponent("", go, {1,0});
	go->AddComponent(pRenderComponent);
	textComponent = go->AddComponent(new Text("5", glm::u8vec3(255, 255, 255), font, go, pRenderComponent));
	go->AddComponent(new PepperCounter(go, textComponent));

	// Create Lives (peters)
	constexpr float iconSize = 30.0f;
	go = pScene->Add(new GameObject(pScene, { iconSize/2 + 5,BurgerTime::WindowHeight() - iconSize, 0 }));
	go->AddComponent(new LivesCounter(iconSize, 9, go));

	// Create What Level (burgers)
	go = pScene->Add(new GameObject(pScene, { BurgerTime::WindowWidth() - iconSize + 5,BurgerTime::WindowHeight() - iconSize, 0 }));
	go->AddComponent(new LevelCounter(iconSize, 3, go));
}
