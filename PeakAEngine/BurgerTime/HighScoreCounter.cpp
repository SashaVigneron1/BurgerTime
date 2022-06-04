#include "pch.h"
#include "HighScoreCounter.h"

#include "PeakAEngine/GameObject.h"
#include "PeakAEngine/Text.h"

#include "Events.h"
#include "ScoreCounter.h"
#include "PeakAEngine/Scene.h"

HighScoreCounter::HighScoreCounter(GameObject* attachedObj, Text* pTextComponent)
	: Component(attachedObj)
	, m_pText{ pTextComponent }
	, m_Score{ 0 }
	, m_fileIO{"HighScore.txt"}
{
	// Load Score
	std::string scoreString = m_fileIO.ReadLine();
	if (!scoreString.empty())
		m_Score = std::stoi(scoreString);

	UpdateText();
}

HighScoreCounter::~HighScoreCounter() = default;

void HighScoreCounter::Update()
{
}

void HighScoreCounter::FixedUpdate()
{
}

void HighScoreCounter::Notify(Component* /*pComponent*/, Event event)
{
	switch (event)
	{
	case Event::GameOver:
		int currScore = m_pGameObject->GetScene()->FindObjectOfType<ScoreCounter>()->GetScore();
		if (currScore > m_Score)
		{
			m_Score = currScore;
			m_fileIO.DeleteAllLines();
			m_fileIO.WriteLine(std::to_string(m_Score));
		}
		break;
	}

	UpdateText();
}

void HighScoreCounter::UpdateText()
{
	std::string text = std::to_string(m_Score);
	if (m_pText) m_pText->SetText(text);
}

void HighScoreCounter::Reset()
{
	// Load Score
	m_fileIO.ReOpenFile();
	m_fileIO.ReturnToStart();
	std::string scoreString = m_fileIO.ReadLine();
	if (!scoreString.empty())
		m_Score = std::stoi(scoreString);

	UpdateText();
}

void HighScoreCounter::SetActiveSceneScoreToMine()
{
	SceneManager::GetInstance().GetActiveScene()->FindObjectOfType<HighScoreCounter>()->SetScore(m_Score);
}

