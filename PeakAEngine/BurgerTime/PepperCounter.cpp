#include "pch.h"
#include "PepperCounter.h"

#include "PeakAEngine/GameObject.h"
#include "PeakAEngine/Text.h"

#include "Events.h"
#include "PeakAEngine/Scene.h"
#include "PeakAEngine/SceneManager.h"

PepperCounter::PepperCounter(GameObject* attachedObj, Text* pTextComponent)
	: Component(attachedObj)
	, m_pText{ pTextComponent }
	, m_PepperCount{ 5 }
{
	UpdateText();
}

PepperCounter::~PepperCounter() = default;

void PepperCounter::Update()
{

}

void PepperCounter::FixedUpdate()
{

}

void PepperCounter::Notify(Component* /*pComponent*/, Event event)
{
	switch (event)
	{
		case Event::OnUsePepper:
			m_PepperCount -= 1;
			break;
	}

	UpdateText();
}

void PepperCounter::UpdateText()
{
	std::string text = std::to_string(m_PepperCount);
	if (m_pText) m_pText->SetText(text);
}

void PepperCounter::SetActiveSceneScoreToMine()
{
	SceneManager::GetInstance().GetActiveScene()->FindObjectOfType<PepperCounter>()->SetPepperCount(m_PepperCount);
}

