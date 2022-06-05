#include "pch.h"
#include "Enemy.h"

#include "BurgerPiece.h"
#include "BurgerTime.h"
#include "Ladder.h"
#include "PeterPepper.h"
#include "PeakAEngine/RaycastCallback.h"
#include "PeakAEngine/Scene.h"
#include "PeakAEngine/SpriteRenderer.h"
#include "PeakAEngine/Time.h"

class PeterPepper;

Enemy::Enemy(SpriteRenderer* pSpriteRenderer, PhysicsComponent* pPhysics, GameObject* attachedObj)
	: Component{ attachedObj }
	, m_pSpriteRenderer{ pSpriteRenderer }
	, m_pPhysics{ pPhysics }
	, m_CanMoveVertically{false}
	, m_LadderCount{ 0 }
	, m_MovementSpeed{ 0.8f }
	, m_IsFalling{ false }
	, m_IsStunned{ false }
	, m_StunTime{ 1.0f }
	, m_AccStunTime{ 0.0f }
	, m_IsMovingLeft{ false }
	, m_IsMovingRight{ false }
	, m_IsMovingUp{ false }
	, m_IsMovingDown{ false }
{
	auto players = m_pGameObject->GetScene()->FindObjectsOfType<PeterPepper>();
	for (int i{}; i < (int)players.size(); ++i)
		m_pPlayers.push_back(players[i]->GetGameObject());

	m_pSpriteRenderer->SetActiveSprite("Walking");
}

Enemy::~Enemy()
{
}

void Enemy::Update()
{
	// Reset MovingStates
	m_IsMovingUp = false;
	m_IsMovingDown = false;
	m_IsMovingLeft = false;
	m_IsMovingRight = false;

	if (m_IsFalling)
		return;

	if (m_IsStunned)
	{
		m_AccStunTime += Time::DeltaTime();
		if (m_AccStunTime >= m_StunTime)
		{
			m_AccStunTime = 0.0f;
			m_IsStunned = false;
			m_pSpriteRenderer->SetActiveSprite("Walking");
		}
		else
			return;
	}

	#pragma region CheckWhatDirectionWeCanMoveIn
	constexpr float halfWidth{ 20 };

	bool canMoveLeft{ false };
	bool canMoveRight{ false };
	bool canMoveDown{ false };
	bool canMoveUp{ false };

	constexpr float horizontalCheckRange{ 20 };
	constexpr float verticalCheckRange{ 30 };

	RaycastCallback leftCallback;
	// If left side on platform
	m_pPhysics->Raycast({ m_pGameObject->GetWorldPosition().x - halfWidth, m_pGameObject->GetWorldPosition().y }, { 0,1 }, horizontalCheckRange, &leftCallback);
	if (leftCallback.m_pOther && leftCallback.ContainsObjectWithTag("Platform")) canMoveLeft = true;
	RaycastCallback rightCallback;
	// If right side on platform
	m_pPhysics->Raycast({ m_pGameObject->GetWorldPosition().x + halfWidth, m_pGameObject->GetWorldPosition().y }, { 0,1 }, horizontalCheckRange, &rightCallback);
	if (rightCallback.m_pOther && rightCallback.ContainsObjectWithTag("Platform")) canMoveRight = true;

	RaycastCallback downCallback;
	// Check Ladder
	m_pPhysics->Raycast({ m_pGameObject->GetWorldPosition().x, m_pGameObject->GetWorldPosition().y }, { 0,1 }, verticalCheckRange, &downCallback);
	if (downCallback.m_pOther && downCallback.ContainsObjectWithTag("Ladder"))
		canMoveDown = true;
	RaycastCallback upCallback;
	m_pPhysics->Raycast({ m_pGameObject->GetWorldPosition().x, m_pGameObject->GetWorldPosition().y }, { 0,-1 }, verticalCheckRange, &upCallback);
	if (upCallback.m_pOther && upCallback.ContainsObjectWithTag("Ladder"))
		canMoveUp = true;
	#pragma endregion

	#pragma region CalculateWhatDirectionWeGoIn
	// Check What Player Is Closest
	GameObject* closestPlayerObj = nullptr;
	float closestDistance = FLT_MAX;
	auto thisPos = GetGameObject()->GetWorldPosition();
	auto closestPlayerPos = glm::fvec3{ 0,0,0 };

	for (auto player : m_pPlayers)
	{
		const auto playerPos = player->GetWorldPosition();
		const auto distance = glm::distance(playerPos, thisPos);

		if (distance < closestDistance)
		{
			closestDistance = distance;
			closestPlayerObj = player;
			closestPlayerPos = player->GetWorldPosition();
		}
	}

	// Check Directions We Can Move In
	constexpr float ignoreDistance{ 1.0f };

	// If Can Move Up && player.y < enemy.y
	if ((m_CanMoveVertically || canMoveUp) && closestPlayerPos.y < thisPos.y && glm::abs(closestPlayerPos.y - thisPos.y) > ignoreDistance)
		m_IsMovingUp = true;
	// If Can Move Down && player.y > enemy.y
	else if ((m_CanMoveVertically || canMoveDown) && closestPlayerPos.y > thisPos.y && glm::abs(closestPlayerPos.y - thisPos.y) > ignoreDistance)
		m_IsMovingDown = true;
	// If Can Move Left && player.x < enemy.x
	else if (canMoveLeft && closestPlayerPos.x < thisPos.x && glm::abs(closestPlayerPos.x - thisPos.x) > ignoreDistance)
		m_IsMovingLeft = true;
	// If Can Move Right && player.x > enemy.x
	else if (canMoveRight && closestPlayerPos.x > thisPos.x && glm::abs(closestPlayerPos.x - thisPos.x) > ignoreDistance)
		m_IsMovingRight = true;
	#pragma endregion
}

void Enemy::FixedUpdate()
{
	if (m_IsFalling)
	{
		m_pGameObject->Translate(0, m_MovementSpeed * 2, 0);

		if (m_pGameObject->GetWorldPosition().y > BurgerTime::WindowHeight())
			m_pGameObject->Destroy();

		return;
	}

	if (m_pBurgerPiece)
	{
		if (m_pBurgerPiece->IsFalling())
		{
			m_pBurgerPiece->AddCollectedEnemy();
			m_IsFalling = true;
			m_pSpriteRenderer->SetActiveSprite("Death");
		}
	}

	// Movement
	bool moving{ false };
	if (m_IsMovingLeft)
	{
		m_pGameObject->Translate(-m_MovementSpeed, 0, 0);
		m_pSpriteRenderer->SetDirection(Direction::FacingLeft);
		moving = true;
	}
	else if (m_IsMovingRight)
	{
		m_pGameObject->Translate(m_MovementSpeed, 0, 0);
		m_pSpriteRenderer->SetDirection(Direction::FacingRight);
		moving = true;
	}
	else if (m_IsMovingDown)
	{
		m_pGameObject->Translate(0, m_MovementSpeed, 0);
		m_pSpriteRenderer->SetDirection(Direction::FacingCamera);
		moving = true;
	}
	else if (m_IsMovingUp)
	{
		m_pGameObject->Translate(0, -m_MovementSpeed, 0);
		m_pSpriteRenderer->SetDirection(Direction::FacingAwayFromCamera);
		moving = true;
	}
}

void Enemy::OnGUI()
{
}

void Enemy::OnTriggerEnter(PhysicsComponent* pOther)
{

	// BURGERS
	const auto isBurger = pOther->GetGameObject()->HasTag("BurgerIngredient");
	if (isBurger)
	{
		auto burger = pOther->GetGameObject()->GetComponent<BurgerPiece>();
		if (burger)
			m_pBurgerPiece = burger;
	}

	// PLAYERS
	const auto isPlayer = pOther->GetGameObject()->HasTag("PeterPepper");
	if (isPlayer && !m_IsStunned)
	{
		// Hurt
		pOther->GetGameObject()->GetComponent<PeterPepper>()->Die();
	}

	// LADDERS
	const auto isLadder = pOther->GetGameObject()->HasTag("Ladder");

	if (isLadder)
	{
		++m_LadderCount;
		if (m_LadderCount > 0)
			m_CanMoveVertically = true;
	}
}

void Enemy::OnTriggerExit(PhysicsComponent* pOther)
{
	const auto isBurger = pOther->GetGameObject()->HasTag("BurgerIngredient");
	if (isBurger)
		m_pBurgerPiece = nullptr;

	const auto isLadder = pOther->GetGameObject()->HasTag("Ladder");

	if (isLadder)
	{
		--m_LadderCount;
		if (m_LadderCount <= 0)
			m_CanMoveVertically = false;
	}
}

void Enemy::Stun()
{
	m_IsStunned = true;
	m_pSpriteRenderer->SetActiveSprite("Stunned");
}
