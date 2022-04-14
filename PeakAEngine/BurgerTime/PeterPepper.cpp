#include "pch.h"
#include "PeterPepper.h"

#include "PeakAEngine/GameObject.h"
#include "Events.h"
#include "3rdParty/imgui-1.87/imgui.h"
#include "PeakAEngine/InputManager.h"
#include "PeakAEngine/Logger.h"
#include "PeakAEngine/PhysicsComponent.h"
#include "PeakAEngine/Time.h"

#include "PeakAEngine/SpriteRenderer.h"

PeterPepper::PeterPepper(SpriteRenderer* pSpriteRenderer, GameObject* attachedObj)
	: Component{ attachedObj }
	, m_pSpriteRenderer{ pSpriteRenderer }
	, m_Lives{ 3 }
	, m_Score{ 0 }
{
}

PeterPepper::~PeterPepper() = default;

void PeterPepper::Update()
{
	bool moving{ false };

	if (InputManager::GetInstance().IsDown('z'))
	{
		m_pGameObject->Translate(0, -200 * Time::DeltaTime(), 0);
		m_pSpriteRenderer->SetDirection(Direction::FacingAwayFromCamera);
		moving = true;
	}
	else if (InputManager::GetInstance().IsDown('s'))
	{
		m_pGameObject->Translate(0, 200 * Time::DeltaTime(), 0);
		moving = true;
		m_pSpriteRenderer->SetDirection(Direction::FacingCamera);
	}
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

	if (!moving)
	{
		m_pSpriteRenderer->SetActiveSprite("Idle");
	}
	else
	{
		m_pSpriteRenderer->SetActiveSprite("Walking");
	}
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

void PeterPepper::OnTriggerEnter(PhysicsComponent* other)
{
	PeterPepper* pepper = other->GetGameObject()->GetComponent<PeterPepper>();

	if (!pepper)
	{
		Logger::LogError("Someone else Hit Me!");
	}
	else
	{
		Logger::LogSuccess("Peter Hit Me!");
	}
}

void PeterPepper::OnTriggerExit(PhysicsComponent*)
{
	Logger::LogError("Something left me!");
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

