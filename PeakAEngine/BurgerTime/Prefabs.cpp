#include "pch.h"
#include "Prefabs.h"

#include <functional>

#include "Achievements.h"


#include "PeakAEngine/GameObject.h"

#include "PeakAEngine/SpriteRenderer.h"
#include "PeakAEngine/PhysicsComponent.h"

#include "PeterPepper.h"
#include "Commands.h"
#include "Ladder.h"
#include "Platform.h"
#include "RenderLayers.h"
#include "PeakAEngine/Scene.h"



void CreatePeterPepper(Scene* pScene, const glm::vec2& position)
{
	auto go = pScene->Add(new GameObject(pScene, {position.x, position.y, 0}));
	//// PETER PEPPER
	// Info
	const float size = 35;
	const float frameSec = 0.05f;
	// Sprite
	SpriteRenderer* pSpriteRenderer = go->AddComponent(new SpriteRenderer(go));
	pSpriteRenderer->AddSprite("Walking", new  Sprite("PeterPepper_Walking.png",
		{
				SpriteRow{Direction::FacingCamera, 0},
				SpriteRow{Direction::FacingLeft, 1},
				SpriteRow{Direction::FacingRight, 1, true},
				SpriteRow{Direction::FacingAwayFromCamera, 2},
		},
		3, frameSec, size, go, (int)Layer::Player));
	pSpriteRenderer->AddSprite("Idle", new  Sprite("PeterPepper_Idle.png",
		{
				SpriteRow{Direction::FacingCamera, 0}
		},
		1, frameSec, size, go, (int)Layer::Player));

	// Physics
	auto physics = go->AddComponent(new PhysicsComponent(go));
	auto pPeterPepper = go->AddComponent(new PeterPepper(pSpriteRenderer, physics, go));
	physics->AddBoxCollider(size, size/4, true, {0,size/2 - size/8});
	physics->OnTriggerEnter = std::bind(&PeterPepper::OnTriggerEnter, pPeterPepper, std::placeholders::_1);
	physics->OnTriggerExit = std::bind(&PeterPepper::OnTriggerExit, pPeterPepper, std::placeholders::_1);
	physics->SetDebugColor({ 1,1,0,0.3f });

	// Observers
	pPeterPepper->AddObserver(&AchievementSystem::GetInstance());

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
	pSpriteRenderer->AddSprite("Idle", new  Sprite("Ladder.png",
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
	physics->AddBoxCollider(tileSize, tileSize / 4, true, {0,-tileSize/2});
	physics->SetDebugColor({ 0,1,1,0.3f });
	// Sprite
	std::string spriteName = (type == PlatformType::normal) ? "Platform.png" : "Platform_Coupled.png";
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
	go->AddComponent(new BurgerPiece(type, tileSize, physics, go));
	physics->AddBoxCollider(tileSize * 2.5f, tileSize, true, {tileSize-10,0});
	physics->SetDebugColor({ 0,0,0,0.3f });
	go->AddTag("BurgerIngredient");
}
