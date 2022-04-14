#include "pch.h"
#include "LivesCounter.h"

#include "PeakAEngine/GameObject.h"
#include "PeakAEngine/Text.h"

#include "PeterPepper.h"
#include "Events.h"

LivesCounter::LivesCounter(GameObject* attachedObj, Text* pTextComponent)
	: Component(attachedObj)
	, m_pText{ pTextComponent }
{

}

LivesCounter::~LivesCounter() = default;

void LivesCounter::Update()
{

}

void LivesCounter::FixedUpdate()
{

}

void LivesCounter::Notify(Component * pComponent, Event event)
{
	if (event == Event::OnPlayerDied)
	{
		auto peter = dynamic_cast<PeterPepper*>(pComponent);
		if (peter)
		{
			std::string text = "Lives: ";
			text += std::to_string(peter->GetLives());
			if (m_pText) m_pText->SetText(text);
		}

	}

}

