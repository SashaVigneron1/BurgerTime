#include "pch.h"
#include "PeterPepper.h"

#include "Enemy.h"
#include "PeakAEngine/GameObject.h"
#include "Events.h"
#include "Ladder.h"
#include "Level.h"
#include "PepperCounter.h"
#include "Platform.h"

#include "3rdParty/imgui-1.87/imgui.h"
#include "PeakAEngine/InputManager.h"
#include "PeakAEngine/PhysicsComponent.h"
#include "PeakAEngine/RaycastCallback.h"
#include "PeakAEngine/Scene.h"
#include "PeakAEngine/Time.h"

#include "PeakAEngine/SpriteRenderer.h"


PeterPepper::PeterPepper(PepperCounter* pPepperCounter, SpriteRenderer* pSpriteRenderer, PhysicsComponent* pPhysics, GameObject* attachedObj)
	: Component{ attachedObj }
	, m_pPepperCounter{ pPepperCounter }
	, m_pSpriteRenderer{ pSpriteRenderer }
	, m_pPhysics{ pPhysics }
	, m_CanMoveVertically{ false }
	, m_LadderCount{ 0 }
	, m_IsDying{ false }
	, m_DeathTimer{ 1.0f }
	, m_AccDeathTimer{ 0.0f }
	, m_InputLeft{ false }
	, m_InputRight{ false }
	, m_InputUp{ false }
	, m_InputDown{ false }
	, m_MovementSpeed{ 1.f }
	, m_IsMovingLeft{ false }
	, m_IsMovingRight{ false }
	, m_IsMovingUp{ false }
	, m_IsMovingDown{ false }
	, m_SpawnPosition{ attachedObj->GetTransform()->GetWorldPosition() }
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


	if (m_IsDying)
	{
		m_AccDeathTimer += Time::DeltaTime();
		if (m_AccDeathTimer > m_DeathTimer)
		{
			m_IsDying = false;
			m_AccDeathTimer = 0.0f;

			glm::vec3 startPos = m_pGameObject->GetWorldPosition();
			glm::vec3 newPos = m_SpawnPosition - startPos;
			m_pGameObject->Translate(newPos.x, newPos.y, newPos.z);
			m_pSpriteRenderer->SetActiveSprite("Idle");
		}
		return;
	}

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

	if ((m_CanMoveVertically || canMoveUp) && m_InputUp)
		m_IsMovingUp = true;
	else if ((m_CanMoveVertically || canMoveDown) && m_InputDown)
		m_IsMovingDown = true;
	else if (canMoveRight && m_InputRight)
		m_IsMovingRight = true;
	else if (canMoveLeft && m_InputLeft)
		m_IsMovingLeft = true;

	m_InputUp = false;
	m_InputDown = false;
	m_InputLeft = false;
	m_InputRight = false;

}
void PeterPepper::FixedUpdate()
{
	if (m_IsDying)
		return;

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
}

void PeterPepper::OnTriggerEnter(PhysicsComponent * other)
{
	auto isLadder = other->GetGameObject()->HasTag("Ladder");

	if (isLadder)
	{
		++m_LadderCount;
		if (m_LadderCount > 0)
			m_CanMoveVertically = true;
	}
}

void PeterPepper::OnTriggerExit(PhysicsComponent * other)
{
	auto isLadder = other->GetGameObject()->HasTag("Ladder");

	if (isLadder)
	{
		--m_LadderCount;
		if (m_LadderCount <= 0)
			m_CanMoveVertically = false;
	}
}

void PeterPepper::Die()
{
	if (!m_IsDying)
	{
		m_IsDying = true;
		Notify(this, Event::OnPlayerDied);
		m_pSpriteRenderer->SetActiveSprite("Death");
	}

}

void PeterPepper::SprayPepper()
{
	if (m_IsDying)
		return;

	if (m_pPepperCounter->GetPepperCount())
	{
		auto thisPos = m_pGameObject->GetWorldPosition();
		auto enemies = m_pGameObject->GetScene()->FindObjectsOfType<Enemy>();
		for (auto enemy : enemies)
		{
			auto enemyPos = enemy->GetGameObject()->GetWorldPosition();
			auto distance = glm::distance(thisPos, enemyPos);
			if (distance < 50.0f)
			{
				enemy->Stun();
			}
		}

		Notify(this, Event::OnUsePepper);
	}
}

