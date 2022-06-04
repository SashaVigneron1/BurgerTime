#include "pch.h"
#include "LevelCounter.h"

#include "PeakAEngine/GameObject.h"
#include "PeakAEngine/Text.h"

#include "Events.h"
#include "RenderLayers.h"
#include "PeakAEngine/Sprite.h"
#include "PeakAEngine/SpriteRenderer.h"

LevelCounter::LevelCounter(float size, int maxLevels, GameObject* attachedObj)
	: Component(attachedObj)
	, m_Level{ 0 }
	, m_MaxLevels{maxLevels}
{
	auto thisGO = GetGameObject();
	auto scene = thisGO->GetScene();
	float offset = size + 5.0f;

	for (int i{}; i < m_MaxLevels; ++i)
	{
		// Create Sprite Object
		auto gameObj = new GameObject(scene);
		gameObj->SetParent(thisGO, false);
		gameObj->SetLocalPosition(0, -offset * i);

		auto spriteRenderer = gameObj->AddComponent(new SpriteRenderer(gameObj));
		spriteRenderer->AddSprite("Idle", new  Sprite("UI/Level.png",
			{
					SpriteRow{Direction::FacingCamera, 0}
			},
			1, 1.f, size, gameObj, (int)Layer::UI));

		m_LevelObjects.push_back(gameObj);
	}

	UpdateUI();
}

LevelCounter::~LevelCounter() = default;

void LevelCounter::Update()
{
	if (InputManager::GetInstance().IsPressed('l'))
		Notify(this, Event::OnLevelComplete);
}

void LevelCounter::FixedUpdate()
{

}

void LevelCounter::Notify(Component* /*pComponent*/, Event event)
{
	if (event == Event::OnLevelComplete)
	{
		++m_Level;
	}

	UpdateUI();
}

void LevelCounter::UpdateUI()
{
	for (int i{}; i < m_MaxLevels; ++i)
	{
		if (i < m_Level)
			m_LevelObjects[i]->SetActive(true);
		else
			m_LevelObjects[i]->SetActive(false);
	}
}

