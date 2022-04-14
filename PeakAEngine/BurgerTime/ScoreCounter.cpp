#include "pch.h"
#include "ScoreCounter.h"

#include "PeakAEngine/GameObject.h"
#include "PeakAEngine/Text.h"

#include "PeterPepper.h"
#include "Events.h"

ScoreCounter::ScoreCounter(GameObject* attachedObj, Text* pTextComponent)
	: Component(attachedObj)
	, m_pText{ pTextComponent }
{

}

ScoreCounter::~ScoreCounter() = default;

void ScoreCounter::Update()
{

}

void ScoreCounter::FixedUpdate()
{

}

void ScoreCounter::Notify(Component* pComponent, Event event)
{
	if (event == Event::OnBurgerFell || event == Event::OnEnemyDied)
	{
		auto peter = dynamic_cast<PeterPepper*>(pComponent);
		if (peter)
		{
			std::string text = "Score: ";
			text += std::to_string(peter->GetScore());
			if (m_pText) m_pText->SetText(text);
		}

	}

}

