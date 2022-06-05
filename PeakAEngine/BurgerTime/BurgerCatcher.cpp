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
		const auto burgerPiece = pOther->GetGameObject()->GetComponent<BurgerPiece>();
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

			// Notify Score System
			const int collectedEnemies = burgerPiece->GetCollectedEnemyCount();
			switch (collectedEnemies)
			{
			case 0:
				Notify(this, Event::OnBurgerFell);
				break;
			case 1:
				Notify(this, Event::OnBurgerFellOneEnemy);
				break;
			case 2:
				Notify(this, Event::OnBurgerFellTwoEnemies);
				break;
			case 3:
				Notify(this, Event::OnBurgerFellThreeEnemies);
				break;
			case 4:
				Notify(this, Event::OnBurgerFellFourEnemies);
				break;
			case 5:
				Notify(this, Event::OnBurgerFellFiveEnemies);
				break;
			case 6:
				Notify(this, Event::OnBurgerFellSixEnemies);
				break;
			}
		}
	}

}

void BurgerCatcher::OnTriggerExit(PhysicsComponent* /*pOther*/)
{
}
