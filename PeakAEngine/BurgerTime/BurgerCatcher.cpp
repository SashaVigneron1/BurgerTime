#include "pch.h"
#include "BurgerCatcher.h"

#include "BurgerPiece.h"
#include "Events.h"
#include "PeakAEngine/GameObject.h"
#include "PeakAEngine/PhysicsComponent.h"

BurgerCatcher::BurgerCatcher(GameObject* go)
	: Component{go}
	, m_StackCount{0}
	, m_HeightPerIngredient{25.0f}
{

}

void BurgerCatcher::Update()
{

}

void BurgerCatcher::OnTriggerEnter(PhysicsComponent* pOther)
{
	if (pOther->GetGameObject()->HasTag("BurgerIngredient"))
	{
		auto burgerPiece = pOther->GetGameObject()->GetComponent<BurgerPiece>();
		if (burgerPiece && !burgerPiece->IsCollected())
		{
			// Stop BurgerPiece From Falling
			burgerPiece->StopFalling();
			burgerPiece->SetCollected();

			// Move burgerPiece to top of stack
			constexpr float yOffset = 60.0f;
			burgerPiece->GetGameObject()->SetWorldPosition(m_pGameObject->GetWorldPosition());
			burgerPiece->GetGameObject()->Translate(0, yOffset + -m_HeightPerIngredient * (float)m_StackCount, 0);

			++m_StackCount;
		}

		// Notify Score System
		Notify(this, Event::OnBurgerFell);
	}

}

void BurgerCatcher::OnTriggerExit(PhysicsComponent* /*pOther*/)
{
}
