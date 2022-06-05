#pragma once
#include "PeakAEngine/BaseComponent.h"
class BurgerPiece;
class SpriteRenderer;
class PhysicsComponent;

class Enemy final : public Component
{
public:
	Enemy(SpriteRenderer* pSpriteRenderer, PhysicsComponent* pPhysics, GameObject* attachedObj);
	virtual ~Enemy() override;
	Enemy(const Enemy& other) = delete;
	Enemy(Enemy&& other) = delete;
	Enemy& operator=(const Enemy& other) = delete;
	Enemy& operator=(Enemy&& other) = delete;

	void Update() override;
	void FixedUpdate() override;
	void OnGUI() override;
	void Render() const override {}

	void OnTriggerEnter(PhysicsComponent* pOther);
	void OnTriggerExit(PhysicsComponent* pOther);

	void Stun();

private:
	//// Variables
	SpriteRenderer* m_pSpriteRenderer;
	PhysicsComponent* m_pPhysics;

	bool m_CanMoveVertically;
	int m_LadderCount;

	// Movement
	bool m_IsFalling;
	bool m_IsStunned;
	float m_AccStunTime;
	float m_StunTime;

	float m_MovementSpeed;

	bool m_IsMovingLeft;
	bool m_IsMovingRight;
	bool m_IsMovingUp;
	bool m_IsMovingDown;

	std::vector<GameObject*> m_pPlayers;
	BurgerPiece* m_pBurgerPiece;
};