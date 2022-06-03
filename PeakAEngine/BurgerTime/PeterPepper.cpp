#include "pch.h"
#include "PeterPepper.h"

#include "PeakAEngine/GameObject.h"
#include "Events.h"
#include "Ladder.h"
#include "Level.h"
#include "Platform.h"

#include "3rdParty/imgui-1.87/imgui.h"
#include "PeakAEngine/InputManager.h"
#include "PeakAEngine/Logger.h"
#include "PeakAEngine/PhysicsComponent.h"
#include "PeakAEngine/RaycastCallback.h"
#include "PeakAEngine/Time.h"

#include "PeakAEngine/SpriteRenderer.h"

PeterPepper::PeterPepper(SpriteRenderer* pSpriteRenderer, PhysicsComponent* pPhysics, GameObject* attachedObj)
	: Component{ attachedObj }
	, m_pSpriteRenderer{ pSpriteRenderer }
	, m_pPhysics{ pPhysics }
	, m_Lives{ 3 }
	, m_Score{ 0 }
	, m_LadderCount{ 0 }
	, m_CanMoveVertically{ false }
	, m_MovementSpeed{ 100.0f }
	, m_pLevel{nullptr}
{
	//m_pLevel = GetGameObject()->GetScene()->FindObjectOfType<Level>();
}

PeterPepper::~PeterPepper() = default;

void PeterPepper::Update()
{
	// ToDo: Up ladder
	// ToDo: Down Ladder

	// Ground Checks
	const float halfWidth{ 20 };

	bool canMoveLeft{ false };
	bool canMoveRight{ false };

	RaycastCallback leftCallback;
	// If left side on platform
	m_pPhysics->Raycast({ m_pGameObject->GetWorldPosition().x - halfWidth, m_pGameObject->GetWorldPosition().y }, { 0,1 }, 75, &leftCallback);
	if (leftCallback.m_pOther && (leftCallback.m_pOther->HasTag("Platform") || leftCallback.m_pOther->HasTag("BurgerPiece") || leftCallback.m_pOther->HasTag("Ladder")))
		canMoveLeft = true;
	RaycastCallback rightCallback;
	// If right side on platform
	m_pPhysics->Raycast({ m_pGameObject->GetWorldPosition().x + halfWidth, m_pGameObject->GetWorldPosition().y }, { 0,1 }, 75, &rightCallback);
	if (rightCallback.m_pOther && (rightCallback.m_pOther->HasTag("Platform") || rightCallback.m_pOther->HasTag("BurgerPiece") || rightCallback.m_pOther->HasTag("Ladder")))
		canMoveRight = true;

	// Movement
	//ToDo: Snap To Level
	bool moving{ false };
	if (m_CanMoveVertically)
	{
		if (InputManager::GetInstance().IsDown('z'))
		{
			m_pGameObject->Translate(0, -m_MovementSpeed * Time::DeltaTime(), 0);
			m_pSpriteRenderer->SetDirection(Direction::FacingAwayFromCamera);
			moving = true;
		}
		else if (InputManager::GetInstance().IsDown('s'))
		{
			m_pGameObject->Translate(0, m_MovementSpeed * Time::DeltaTime(), 0);
			m_pSpriteRenderer->SetDirection(Direction::FacingCamera);
			moving = true;
		}
	}
	if (canMoveRight && InputManager::GetInstance().IsDown('d'))
	{
		m_pGameObject->Translate(m_MovementSpeed * Time::DeltaTime(), 0, 0);
		m_pSpriteRenderer->SetDirection(Direction::FacingRight);
		moving = true;
	}
	else if (canMoveLeft && InputManager::GetInstance().IsDown('q'))
	{
		m_pGameObject->Translate(-m_MovementSpeed * Time::DeltaTime(), 0, 0);
		m_pSpriteRenderer->SetDirection(Direction::FacingLeft);
		moving = true;
	}

	if (!moving)
		m_pSpriteRenderer->SetActiveSprite("Idle");
	else
		m_pSpriteRenderer->SetActiveSprite("Walking");

	if (InputManager::GetInstance().IsPressed('r'))
	{
		m_pGameObject->Destroy();
	}

	if (m_pLevel) m_pLevel->SnapToGrid(GetGameObject()->GetTransform());
}
void PeterPepper::FixedUpdate()
{

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
	// Teachers: put m_Score in the observer, not in the subject
	// ToDo: Ask Teachers


	// This magic number is just for testing purposes
	m_Score += 250;
	Notify(this, Event::OnEnemyDied);
}

