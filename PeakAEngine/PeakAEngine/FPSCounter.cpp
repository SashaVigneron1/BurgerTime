#include "PeakAEnginePCH.h"
#include "FPSCounter.h"

#include "GameObject.h"
#include "Text.h"
#include "Time.h"

FPSCounter::FPSCounter(GameObject* attachedObj, Text* pTextComponent)
	: Component(attachedObj)
	, m_pText{pTextComponent}
	, m_CurrIndex(0)
	, m_NrOfTimes(30)
{
	m_FrameTimes.resize(m_NrOfTimes);
}

FPSCounter::~FPSCounter() = default;

void FPSCounter::Update()
{
	m_FrameTimes[m_CurrIndex] = 1 / Time::DeltaTime();

	if (m_CurrIndex %  m_NrOfTimes == 0)
	{
		float sum = 0;
		int avg = 0;

		for (int i = 0; i < m_NrOfTimes; i++)
		{
			sum += m_FrameTimes[i];
		}
		avg = int(sum / m_NrOfTimes);

		if (m_pText) m_pText->SetText("FPS: " + std::to_string(avg));
	}

	++m_CurrIndex %= m_NrOfTimes;
}

void FPSCounter::FixedUpdate()
{
	
}

