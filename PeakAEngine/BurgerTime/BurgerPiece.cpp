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

BurgerPiece::BurgerPiece(BurgerPieceType type, float tileSize, PhysicsComponent* pPhysics, GameObject* go)
	: Component{ go }
	, m_Type{ type }
	, m_IsFalling{false}
	, m_IsCollected{false}
	, m_pPhysics{ pPhysics }
	, m_FallingSpeed{ 80.0f }
	, m_MinFallingTime{0.2f}
	, m_AccFallingTime{}
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
	float partOffset = tileSize * (3.f/5.f);
	float burgerOffsetX = -14.0f;

	// LEFT
	#pragma region Left
	// GameObject
	auto gameObj = new GameObject(scene);
	gameObj->SetParent(thisGO, false);
	gameObj->SetLocalPosition(burgerOffsetX, 0);
	gameObj->AddTag("IngredientPart");
	gameObj->AddTag("BurgerPiece");
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

	m_pParts.push_back(burgerPiecePart);
	#pragma endregion

	// MID LEFT
	#pragma region MidLeft
	// GameObject
	gameObj = new GameObject(scene);
	gameObj->SetParent(thisGO, false);
	gameObj->SetLocalPosition(burgerOffsetX + partOffset, 0);
	gameObj->AddTag("IngredientPart");
	gameObj->AddTag("BurgerPiece");
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
	m_pParts.push_back(burgerPiecePart);
	#pragma endregion

	//// MID RIGHT
	#pragma region MidRight
	// GameObject
	gameObj = new GameObject(scene);
	gameObj->SetParent(thisGO, false);
	gameObj->SetLocalPosition(burgerOffsetX + 2* partOffset, 0);
	gameObj->AddTag("IngredientPart");
	gameObj->AddTag("BurgerPiece");
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
	m_pParts.push_back(burgerPiecePart);
	#pragma endregion

	//// RIGHT
	#pragma region Right
	// GameObject
	gameObj = new GameObject(scene);
	gameObj->SetParent(thisGO, false);
	gameObj->SetLocalPosition(burgerOffsetX + 3*partOffset, 0);
	gameObj->AddTag("IngredientPart");
	gameObj->AddTag("BurgerPiece");
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
	m_pParts.push_back(burgerPiecePart);
	#pragma endregion
}

void BurgerPiece::Update()
{
	if (m_IsCollected)
		return;

	if (m_IsFalling)
	{
		// Shift Down
		m_pGameObject->Translate(0, m_FallingSpeed * Time::DeltaTime(), 0);

		m_AccFallingTime += Time::DeltaTime();
		if (m_AccFallingTime > m_MinFallingTime)
		{
			float raycastYOffset{ 0.f };
			float range{ 10.0f };

			RaycastCallback raycastDownCallback;
			// If left side on platform
			m_pPhysics->Raycast({ m_pGameObject->GetWorldPosition().x, m_pGameObject->GetWorldPosition().y + raycastYOffset }, { 0,1 }, range, &raycastDownCallback);
			if (raycastDownCallback.m_pOther && raycastDownCallback.m_pOther->HasTag("BurgerIngredient"))
			{
				// If Other piece: Wait here & set other piece falling
				auto otherBurger = raycastDownCallback.m_pOther->GetComponent<BurgerPiece>();

				if (otherBurger->IsCollected())
					return;

				if (otherBurger)
					otherBurger->SetFalling();

				// If Catcher: Notify Score

				// Move this obj to other objects position
				auto otherPos = raycastDownCallback.m_pOther->GetWorldPosition();
				auto thisPos = m_pGameObject->GetWorldPosition();
				m_pGameObject->Translate(0, otherPos.y - thisPos.y, 0);

				// Put Ingredient Parts Back To Original Position
				for (auto part : m_pParts)
				{
					part->ResetDownPosition();
				}
				// Stop Falling
				m_IsFalling = false;
				m_AccFallingTime = 0.0f;
			}
		}
	}
}

void BurgerPiece::FixedUpdate()
{
}

void BurgerPiece::SetFalling()
{
	if (m_IsCollected)
		return;

	m_IsFalling = true;
	for (auto part : m_pParts)
	{
		part->ResetDownPosition();
	}
}

void BurgerPiece::StopFalling()
{
	m_IsFalling = false;
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
