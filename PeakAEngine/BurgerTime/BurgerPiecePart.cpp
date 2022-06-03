#include "pch.h"
#include "BurgerPiecePart.h"

#include "Events.h"
#include "PeakAEngine/GameObject.h"
#include "PeakAEngine/PhysicsComponent.h"

BurgerPiecePart::BurgerPiecePart(GameObject* go)
	: Component{go}
	, m_DownOffset{10.f}
	, m_IsDown{false}
{

}

void BurgerPiecePart::Update()
{
}

void BurgerPiecePart::FixedUpdate()
{
}

void BurgerPiecePart::OnTriggerEnter(PhysicsComponent* pOther)
{
	if (!m_IsDown)
	{
		if (pOther->GetGameObject()->HasTag("PeterPepper"))
		{
			m_IsDown = true;

			// Shift Down
			auto newPos = GetGameObject()->GetLocalPosition();
			newPos.y += m_DownOffset;
			GetGameObject()->SetLocalPosition(newPos);

			Notify(this, Event::OnBurgerPieceDown);
		}
	}
}

void BurgerPiecePart::OnTriggerExit(PhysicsComponent* /*pOther*/)
{
}

void BurgerPiecePart::ResetDownPosition()
{
	if (m_IsDown)
	{
		m_IsDown = false;
		auto newPos = GetGameObject()->GetLocalPosition();
		newPos.y -= m_DownOffset;
		GetGameObject()->SetLocalPosition(newPos);
	}
}
