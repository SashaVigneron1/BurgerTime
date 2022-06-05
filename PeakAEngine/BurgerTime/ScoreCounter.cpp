#include "pch.h"
#include "ScoreCounter.h"

#include "PeakAEngine/GameObject.h"
#include "PeakAEngine/Text.h"

#include "Events.h"
#include "PeakAEngine/Scene.h"
#include "PeakAEngine/SceneManager.h"

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
		case Event::OnBurgerFellOneEnemy:
			m_Score += 500;
			break;
		case Event::OnBurgerFellTwoEnemies:
			m_Score += 1000;
			break;
		case Event::OnBurgerFellThreeEnemies:
			m_Score += 2000;
			break;
		case Event::OnBurgerFellFourEnemies:
			m_Score += 4000;
			break;
		case Event::OnBurgerFellFiveEnemies:
			m_Score += 8000;
			break;
		case Event::OnBurgerFellSixEnemies:
			m_Score += 16000;
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

void ScoreCounter::SetActiveSceneScoreToMine()
{
	SceneManager::GetInstance().GetActiveScene()->FindObjectOfType<ScoreCounter>()->SetScore(m_Score);
}

