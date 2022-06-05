#include "pch.h"
#include "LivesCounter.h"

#include "PeakAEngine/GameObject.h"
#include "PeakAEngine/Text.h"

#include "PeterPepper.h"
#include "Events.h"
#include "LevelCompleter.h"
#include "RenderLayers.h"
#include "PeakAEngine/Scene.h"
#include "PeakAEngine/SceneManager.h"
#include "PeakAEngine/Sprite.h"
#include "PeakAEngine/SpriteRenderer.h"

LivesCounter::LivesCounter(float size, int maxLives, GameObject* attachedObj)
	: Component(attachedObj)
	, m_Lives{maxLives}
	, m_MaxLives{maxLives}
{
	auto thisGO = GetGameObject();
	auto scene = thisGO->GetScene();
	float offset = size + 5.0f;

	for(int i{}; i < m_MaxLives; ++i)
	{
		// Create Sprite Object
		auto gameObj = new GameObject(scene);
		gameObj->SetParent(thisGO, false);
		gameObj->SetLocalPosition(0, -offset * i);

		auto spriteRenderer = gameObj->AddComponent(new SpriteRenderer(gameObj));
		spriteRenderer->AddSprite("Idle", new  Sprite("UI/Life.png",
			{
					SpriteRow{Direction::FacingCamera, 0}
			},
			1, 1.f, size, gameObj, (int)Layer::UI));

		m_LivesObjects.push_back(gameObj);
	}

	UpdateUI();
}

LivesCounter::~LivesCounter() = default;

void LivesCounter::Update()
{
	//ToDo: Remove
	if (InputManager::GetInstance().IsPressed('l'))
		Notify(this, Event::OnPlayerDied);
}

void LivesCounter::FixedUpdate()
{

}

void LivesCounter::Notify(Component * /*pComponent*/, Event event)
{
	if (event == Event::OnPlayerDied)
	{
		--m_Lives;

		if (m_Lives <= 0)
		{
			m_pGameObject->GetScene()->FindObjectOfType<LevelCompleter>()->ResetLevelNextFrame();
			SceneManager::GetInstance().LoadScene("MainMenu");
		}
	}

	UpdateUI();
}

void LivesCounter::UpdateUI()
{
	for(int i{}; i < m_MaxLives; ++i)
	{
		if (i < m_Lives)
			m_LivesObjects[i]->SetActive(true);
		else
			m_LivesObjects[i]->SetActive(false);
	}
}

void LivesCounter::SetActiveSceneScoreToMine()
{
	SceneManager::GetInstance().GetActiveScene()->FindObjectOfType<LivesCounter>()->SetLives(m_Lives);
}

