#include "pch.h"
#include "LevelCompleter.h"

#include "BurgerPiece.h"
#include "Events.h"
#include "HighScoreCounter.h"
#include "Level.h"
#include "LivesCounter.h"
#include "PepperCounter.h"
#include "ScoreCounter.h"
#include "PeakAEngine/GameObject.h"
#include "PeakAEngine/Logger.h"
#include "PeakAEngine/Scene.h"
#include "PeakAEngine/SceneManager.h"

LevelCompleter::LevelCompleter(bool isLastLevel, Level* pLevel, GameObject* pGameObject)
	: Component{ pGameObject }
	, m_IsLastLevel{ isLastLevel }
	, m_pLevel{ pLevel }
	, m_HasReset{ false }
{
}

LevelCompleter::~LevelCompleter()
{
}

void LevelCompleter::Update()
{
	if (m_ShouldReset)
	{
		if (!m_HasReset)
		{
			m_ShouldReset = false;
			m_HasReset = true;

			m_pGameObject->GetScene()->FindObjectOfType<HighScoreCounter>()->Notify(this, Event::GameOver);

			// Reset This Level
			m_pLevel->Reset();
		}
	}

	for(auto burgerPiece : m_pBurgerPieces)
	{
		if (!burgerPiece->IsCollected())
			return;
	}

	if (!m_HasReset)
	{
		if (!m_IsLastLevel)
		{
			SceneManager::GetInstance().LoadNextScene();

			// Update New Scene Variables
			m_pGameObject->GetScene()->FindObjectOfType<ScoreCounter>()->SetActiveSceneScoreToMine();
			m_pGameObject->GetScene()->FindObjectOfType<LivesCounter>()->SetActiveSceneScoreToMine();
			m_pGameObject->GetScene()->FindObjectOfType<PepperCounter>()->SetActiveSceneScoreToMine();
			m_pGameObject->GetScene()->FindObjectOfType<HighScoreCounter>()->SetActiveSceneScoreToMine();

			// Reset This Level
			m_HasReset = true;
			m_pLevel->Reset();

		}
		else
		{
			m_pGameObject->GetScene()->FindObjectOfType<HighScoreCounter>()->Notify(this, Event::GameOver);

			// Reset This Level
			m_HasReset = true;
			m_pLevel->Reset();

			SceneManager::GetInstance().LoadScene("MainMenu");

		}
	}
	
}

void LevelCompleter::Reset()
{
	m_HasReset = false;
	m_pBurgerPieces.clear();
}

void LevelCompleter::ResetLevelNextFrame()
{
	m_ShouldReset = true;

	
}
