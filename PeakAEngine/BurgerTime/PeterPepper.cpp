#include "pch.h"
#include "PeterPepper.h"

#include "PeakAEngine/GameObject.h"
#include "Events.h"
#include "Ladder.h"
#include "Level.h"
#include "PepperCounter.h"
#include "Platform.h"

#include "3rdParty/imgui-1.87/imgui.h"
#include "PeakAEngine/InputManager.h"
#include "PeakAEngine/Logger.h"
#include "PeakAEngine/PhysicsComponent.h"
#include "PeakAEngine/RaycastCallback.h"
#include "PeakAEngine/Time.h"

#include "PeakAEngine/SpriteRenderer.h"


PeterPepper::PeterPepper(PepperCounter* pPepperCounter, SpriteRenderer* pSpriteRenderer, PhysicsComponent* pPhysics, GameObject* attachedObj)
	: Component{ attachedObj }
	, m_pPepperCounter{ pPepperCounter }
	, m_pSpriteRenderer{ pSpriteRenderer }
	, m_pPhysics{ pPhysics }
	, m_Lives{ 3 }
	, m_Score{ 0 }
	, m_LadderCount{ 0 }
	, m_CanMoveVertically{ false }
	, m_IsMovingLeft{ false }
	, m_IsMovingRight{ false }
	, m_IsMovingUp{ false }
	, m_IsMovingDown{ false }
	, m_MovementSpeed{ 1.f }
{
}

PeterPepper::~PeterPepper() = default;

void PeterPepper::Update()
{
	// Reset Input
	m_IsMovingLeft = false;
	m_IsMovingRight = false;
	m_IsMovingUp = false;
	m_IsMovingDown = false;

	// Ground Checks
	const float halfWidth{ 20 };

	bool canMoveLeft{ false };
	bool canMoveRight{ false };
	bool canMoveDown{ false };
	bool canMoveUp{ false };

	constexpr float horizontalCheckRange{ 20 };
	constexpr float verticalCheckRange{ 75 };

	RaycastCallback leftCallback;
	// If left side on platform
	m_pPhysics->Raycast({ m_pGameObject->GetWorldPosition().x - halfWidth, m_pGameObject->GetWorldPosition().y }, { 0,1 }, horizontalCheckRange, &leftCallback);
	if (leftCallback.m_pOther && leftCallback.ContainsObjectWithTag("Platform")) canMoveLeft = true;
	RaycastCallback rightCallback;
	// If right side on platform
	m_pPhysics->Raycast({ m_pGameObject->GetWorldPosition().x + halfWidth, m_pGameObject->GetWorldPosition().y }, { 0,1 }, horizontalCheckRange, &rightCallback);
	if (rightCallback.m_pOther && rightCallback.ContainsObjectWithTag("Platform")) canMoveRight = true;

	RaycastCallback downCallback;
	// Check Ladder
	m_pPhysics->Raycast({ m_pGameObject->GetWorldPosition().x, m_pGameObject->GetWorldPosition().y }, { 0,1 }, verticalCheckRange, &downCallback);
	if (downCallback.m_pOther && downCallback.ContainsObjectWithTag("Ladder"))
		canMoveDown = true;
	RaycastCallback upCallback;
	m_pPhysics->Raycast({ m_pGameObject->GetWorldPosition().x, m_pGameObject->GetWorldPosition().y }, { 0,-1 }, verticalCheckRange, &upCallback);
	if (upCallback.m_pOther && upCallback.ContainsObjectWithTag("Ladder"))
		canMoveUp = true;

	if ((m_CanMoveVertically || canMoveUp) && InputManager::GetInstance().IsDown('z'))
		m_IsMovingUp = true;
	else if ((m_CanMoveVertically || canMoveDown) && InputManager::GetInstance().IsDown('s'))
		m_IsMovingDown = true;
	else if (canMoveRight && InputManager::GetInstance().IsDown('d'))
		m_IsMovingRight = true;
	else if (canMoveLeft && InputManager::GetInstance().IsDown('q'))
		m_IsMovingLeft = true;

	if (InputManager::GetInstance().IsPressed('e'))
	{
		if (m_pPepperCounter->GetPepperCount())
		{
			//ToDo: Use Pepper
			Notify(this, Event::OnUsePepper);
		}
	}	

}
void PeterPepper::FixedUpdate()
{
	// Movement
	bool moving{ false };
	if (m_IsMovingLeft)
	{
		m_pGameObject->Translate(-m_MovementSpeed, 0, 0);
		m_pSpriteRenderer->SetDirection(Direction::FacingLeft);
		moving = true;
	}
	else if (m_IsMovingRight)
	{
		m_pGameObject->Translate(m_MovementSpeed, 0, 0);
		m_pSpriteRenderer->SetDirection(Direction::FacingRight);
		moving = true;
	}
	else if (m_IsMovingDown)
	{
		m_pGameObject->Translate(0, m_MovementSpeed, 0);
		m_pSpriteRenderer->SetDirection(Direction::FacingCamera);
		moving = true;
	}
	else if (m_IsMovingUp)
	{
		m_pGameObject->Translate(0, -m_MovementSpeed, 0);
		m_pSpriteRenderer->SetDirection(Direction::FacingAwayFromCamera);
		moving = true;
	}

	if (!moving)
		m_pSpriteRenderer->SetActiveSprite("Idle");
	else
		m_pSpriteRenderer->SetActiveSprite("Walking");
}
void PeterPepper::OnGUI()
{
	// Just a test
	/*ImGui::Begin("Hello");

	ImGui::Text("Hello Again!");

	ImGui::End();*/
}

void PeterPepper::OnTriggerEnter(PhysicsComponent * other)
{
	Ladder* ladder = other->GetGameObject()->GetComponent<Ladder>();

	if (ladder)
	{
		++m_LadderCount;
		if (m_LadderCount > 0)
			m_CanMoveVertically = true;
	}
}

void PeterPepper::OnTriggerExit(PhysicsComponent * other)
{
	Ladder* ladder = other->GetGameObject()->GetComponent<Ladder>();

	if (ladder)
	{
		--m_LadderCount;
		if (m_LadderCount <= 0)
			m_CanMoveVertically = false;
	}
}

void PeterPepper::Die()
{
	--m_Lives;
	Notify(this, Event::OnPlayerDied);
}

void PeterPepper::KillEnemy()
{

	//ToDo: Cleanup this code

	// This magic number is just for testing purposes
	m_Score += 250;
	Notify(this, Event::OnEnemyDied);
}

