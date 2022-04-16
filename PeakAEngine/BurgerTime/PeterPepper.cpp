#include "pch.h"
#include "PeterPepper.h"

#include "PeakAEngine/GameObject.h"
#include "Events.h"
#include "Ladder.h"
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
	, m_CanMoveHorizontally{ false }
	, m_CanMoveVertically{ false }
{
}

PeterPepper::~PeterPepper() = default;

void PeterPepper::Update()
{
	//ToDo: More Efficient

	RaycastCallback callback;
	m_pPhysics->Raycast({ m_pGameObject->GetWorldPosition().x, m_pGameObject->GetWorldPosition().y }, { 0,1 }, 100, &callback);
	if (callback.m_pOther && callback.m_pOther->GetComponent<Platform>())
	{
		Logger::LogInfo(std::to_string(callback.m_fraction));
		m_CanMoveHorizontally = true;
	}
	else
	{
		m_CanMoveHorizontally = false;
	}

	bool moving{ false };
	if (m_CanMoveVertically)
	{
		if (InputManager::GetInstance().IsDown('z'))
		{
			m_pGameObject->Translate(0, -200 * Time::DeltaTime(), 0);
			m_pSpriteRenderer->SetDirection(Direction::FacingAwayFromCamera);
			moving = true;
		}
		else if (InputManager::GetInstance().IsDown('s'))
		{
			m_pGameObject->Translate(0, 200 * Time::DeltaTime(), 0);
			m_pSpriteRenderer->SetDirection(Direction::FacingCamera);
			moving = true;
		}
	}
	if (m_CanMoveHorizontally)
	{
		if (InputManager::GetInstance().IsDown('d'))
		{
			m_pGameObject->Translate(200 * Time::DeltaTime(), 0, 0);
			m_pSpriteRenderer->SetDirection(Direction::FacingRight);
			moving = true;
		}
		else if (InputManager::GetInstance().IsDown('q'))
		{
			m_pGameObject->Translate(-200 * Time::DeltaTime(), 0, 0);
			m_pSpriteRenderer->SetDirection(Direction::FacingLeft);
			moving = true;
		}
	}

	if (!moving)
		m_pSpriteRenderer->SetActiveSprite("Idle");
	else
		m_pSpriteRenderer->SetActiveSprite("Walking");
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

