#include "pch.h"
#include "BurgerPiece.h"

#include "BurgerPiecePart.h"
#include "Events.h"
#include "RenderLayers.h"
#include "PeakAEngine/GameObject.h"
#include "PeakAEngine/PhysicsComponent.h"
#include "PeakAEngine/SpriteRenderer.h"
#include "PeakAEngine/Time.h"
#include "PeakAEngine/RaycastCallback.h"

BurgerPiece::BurgerPiece(BurgerPieceType type, PhysicsComponent* pPhysics, GameObject* go)
	: Component{ go }
	, m_Type{ type }
	, m_IsFalling{false}
	, m_pPhysics{ pPhysics }
	, m_FallingSpeed{ 80.0f }
{
	// Spawn 4 BurgerPieceParts

	std::string name;
	switch (m_Type)
	{
	case BurgerPieceType::UpperBun:
		name = "Bun_Top";
		break;
	case BurgerPieceType::LowerBun:
		name = "Bun_Bottom";
		break;
	case BurgerPieceType::Cheese:
		name = "Cheese";
		break;
	case BurgerPieceType::Patty:
		name = "Patty";
		break;
	case BurgerPieceType::Tomato:
		name = "Tomato";
		break;
	case BurgerPieceType::Salad:
		name = "Salad";
		break;
	}

	auto thisGO = GetGameObject();
	auto scene = thisGO->GetScene();
	float partOffset = 20.0f;

	// LEFT
	#pragma region Left
	// GameObject
	auto gameObj = new GameObject(scene);
	gameObj->SetParent(thisGO, false);
	gameObj->SetLocalPosition(-2*partOffset, 0);
	gameObj->AddTag("IngredientPart");
	auto burgerPiecePart = gameObj->AddComponent(new BurgerPiecePart(gameObj));
	burgerPiecePart->AddObserver(this);

	// Sprite
	auto pSpriteRenderer = gameObj->AddComponent(new SpriteRenderer(gameObj));
	pSpriteRenderer->AddSprite("Idle", new  Sprite("Ingredients/" + name + "/Left.png",
		{
				SpriteRow{Direction::FacingCamera, 0}
		},
		1, 1.f, partOffset, gameObj, (int)Layer::Burger));

	// Physics
	auto physics = gameObj->AddComponent(new PhysicsComponent(gameObj));
	physics->AddBoxCollider(partOffset, partOffset, true);
	physics->OnTriggerEnter = std::bind(&BurgerPiecePart::OnTriggerEnter, burgerPiecePart, std::placeholders::_1);
	physics->OnTriggerExit = std::bind(&BurgerPiecePart::OnTriggerExit, burgerPiecePart, std::placeholders::_1);

	gameObj->AddTag("BurgerPiece");
	m_pParts.push_back(burgerPiecePart);
	#pragma endregion

	// MID LEFT
	#pragma region MidLeft
	// GameObject
	gameObj = new GameObject(scene);
	gameObj->SetParent(thisGO, false);
	gameObj->SetLocalPosition(-partOffset, 0);
	gameObj->AddTag("IngredientPart");
	burgerPiecePart = gameObj->AddComponent(new BurgerPiecePart(gameObj));
	burgerPiecePart->AddObserver(this);

	// Sprite
	pSpriteRenderer = gameObj->AddComponent(new SpriteRenderer(gameObj));
	pSpriteRenderer->AddSprite("Idle", new  Sprite("Ingredients/" + name + "/Mid_Left.png",
		{
				SpriteRow{Direction::FacingCamera, 0}
		},
		1, 1.f, partOffset, gameObj, (int)Layer::Burger));

	// Physics
	physics = gameObj->AddComponent(new PhysicsComponent(gameObj));
	physics->AddBoxCollider(partOffset, partOffset, true);
	physics->OnTriggerEnter = std::bind(&BurgerPiecePart::OnTriggerEnter, burgerPiecePart, std::placeholders::_1);
	physics->OnTriggerExit = std::bind(&BurgerPiecePart::OnTriggerExit, burgerPiecePart, std::placeholders::_1);
	gameObj->AddTag("BurgerPiece");
	m_pParts.push_back(burgerPiecePart);
	#pragma endregion

	//// MID RIGHT
	#pragma region MidRight
	// GameObject
	gameObj = new GameObject(scene);
	gameObj->SetParent(thisGO, false);
	gameObj->SetLocalPosition(0, 0);
	gameObj->AddTag("IngredientPart");
	burgerPiecePart = gameObj->AddComponent(new BurgerPiecePart(gameObj));
	burgerPiecePart->AddObserver(this);

	// Sprite
	pSpriteRenderer = gameObj->AddComponent(new SpriteRenderer(gameObj));
	pSpriteRenderer->AddSprite("Idle", new  Sprite("Ingredients/" + name + "/Mid_Right.png",
		{
				SpriteRow{Direction::FacingCamera, 0}
		},
		1, 1.f, partOffset, gameObj, (int)Layer::Burger));

	// Physics
	physics = gameObj->AddComponent(new PhysicsComponent(gameObj));
	physics->AddBoxCollider(partOffset, partOffset, true);
	physics->OnTriggerEnter = std::bind(&BurgerPiecePart::OnTriggerEnter, burgerPiecePart, std::placeholders::_1);
	physics->OnTriggerExit = std::bind(&BurgerPiecePart::OnTriggerExit, burgerPiecePart, std::placeholders::_1);
	gameObj->AddTag("BurgerPiece");
	m_pParts.push_back(burgerPiecePart);
	#pragma endregion

	//// RIGHT
	#pragma region Right
	// GameObject
	gameObj = new GameObject(scene);
	gameObj->SetParent(thisGO, false);
	gameObj->SetLocalPosition(partOffset, 0);
	gameObj->AddTag("IngredientPart");
	burgerPiecePart = gameObj->AddComponent(new BurgerPiecePart(gameObj));
	burgerPiecePart->AddObserver(this);

	// Sprite
	pSpriteRenderer = gameObj->AddComponent(new SpriteRenderer(gameObj));
	pSpriteRenderer->AddSprite("Idle", new  Sprite("Ingredients/" + name + "/Right.png",
		{
				SpriteRow{Direction::FacingCamera, 0}
		},
		1, 1.f, partOffset, gameObj, (int)Layer::Burger));

	// Physics
	physics = gameObj->AddComponent(new PhysicsComponent(gameObj));
	physics->AddBoxCollider(partOffset, partOffset, true);
	physics->OnTriggerEnter = std::bind(&BurgerPiecePart::OnTriggerEnter, burgerPiecePart, std::placeholders::_1);
	physics->OnTriggerExit = std::bind(&BurgerPiecePart::OnTriggerExit, burgerPiecePart, std::placeholders::_1);
	gameObj->AddTag("BurgerPiece");
	m_pParts.push_back(burgerPiecePart);
	#pragma endregion
}

void BurgerPiece::Update()
{

}

void BurgerPiece::FixedUpdate()
{
	if (m_IsFalling)
	{
		// Shift Down
		auto newPos = GetGameObject()->GetLocalPosition();
		newPos.y += m_FallingSpeed * Time::FixedTime();
		GetGameObject()->SetLocalPosition(newPos);

		RaycastCallback raycastDownCallback;
		// If left side on platform
		m_pPhysics->Raycast({ m_pGameObject->GetWorldPosition().x, m_pGameObject->GetWorldPosition().y }, { 0,1 }, 75, &raycastDownCallback);
		if (raycastDownCallback.m_pOther)
		{
			// If Other piece: Wait here & set other piece falling

			// If Catcher: Notify Score

			//m_IsFalling = false;
		}
	}
}

void BurgerPiece::Notify(Component* /*pComponent*/, Event event)
{
	// Check if all parts are down
	if (event == Event::OnBurgerPieceDown)
	{
		for(auto part : m_pParts)
		{
			if (!part->IsDown())
				return;
		}

		m_IsFalling = true;
	}

}
