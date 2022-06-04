#include "pch.h"
#include "ScoreCounter.h"

#include "PeakAEngine/GameObject.h"
#include "PeakAEngine/Text.h"

#include "Events.h"

ScoreCounter::ScoreCounter(GameObject* attachedObj, Text* pTextComponent)
	: Component(attachedObj)
	, m_pText{ pTextComponent }
	, m_Score{ 0 }
{
	UpdateText();
}

ScoreCounter::~ScoreCounter() = default;

void ScoreCounter::Update()
{

}

void ScoreCounter::FixedUpdate()
{

}

void ScoreCounter::Notify(Component* /*pComponent*/, Event event)
{
	switch (event)
	{
		case Event::OnBurgerFell:
			m_Score += 50;
			break;
		case Event::OnEnemyDied:
			m_Score += 100;
			break;
		case Event::OnPlayerDied:
			m_Score = 0;
			break;
	}

	UpdateText();
}

void ScoreCounter::UpdateText()
{
	std::string text = std::to_string(m_Score);
	if (m_pText) m_pText->SetText(text);
}

