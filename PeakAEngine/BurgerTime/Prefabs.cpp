#include "pch.h"
#include "Prefabs.h"

#include <functional>

#include "Achievements.h"


#include "PeakAEngine/GameObject.h"
#include "PeakAEngine/InputManager.h"

#include "PeakAEngine/SpriteRenderer.h"
#include "PeakAEngine/PhysicsComponent.h"

#include "PeterPepper.h"
#include "Commands.h"

GameObject* CreatePeterPepper(Scene* pScene, const glm::vec2& position)
{
	auto go = new GameObject(pScene, {position.x, position.y, 0});
	//// PETER PEPPER
	// Info
	float size = 100;
	// Sprite
	SpriteRenderer* pSpriteRenderer = go->AddComponent(new SpriteRenderer(go));
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

	// Physics
	PeterPepper* pPeterPepper = go->AddComponent(new PeterPepper(pSpriteRenderer, go));
	auto physics = go->AddComponent(new PhysicsComponent(go));
	physics->AddBoxCollider(size, size, true);
	physics->OnTriggerEnter = std::bind(&PeterPepper::OnTriggerEnter, pPeterPepper, std::placeholders::_1);
	physics->OnTriggerExit = std::bind(&PeterPepper::OnTriggerExit, pPeterPepper, std::placeholders::_1);

	// Observers
	pPeterPepper->AddObserver(&AchievementSystem::GetInstance());

	// Commands
	auto pPeterPepperDieCommand = new PeterPepper_Die(pPeterPepper);
	auto* pPeterPepperKillEnemyCommand = new PeterPepper_KillEnemy(pPeterPepper);
	InputManager::GetInstance().AddCommand('z', pPeterPepperDieCommand);
	InputManager::GetInstance().AddCommand('d', pPeterPepperKillEnemyCommand);

	return go;
}
