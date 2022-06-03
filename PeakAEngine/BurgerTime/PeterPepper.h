#pragma once
#include "PeakAEngine/BaseComponent.h"
#include "PeakAEngine/Subject.h"

class Level;
class PhysicsComponent;
class SpriteRenderer;

class PeterPepper final : public Component, public Subject
{
public:
	PeterPepper(SpriteRenderer* pSpriteRenderer, PhysicsComponent* pPhysics, GameObject* attachedObj);
	virtual ~PeterPepper() override;
	PeterPepper(const PeterPepper& other) = delete;
	PeterPepper(PeterPepper&& other) = delete;
	PeterPepper& operator=(const PeterPepper& other) = delete;
	PeterPepper& operator=(PeterPepper&& other) = delete;

	int GetLives() const { return m_Lives; }
	int GetScore() const { return m_Score; }

	void Update() override;
	void FixedUpdate() override;
	void OnGUI() override;
	void Render() const override {}

	void OnTriggerEnter(PhysicsComponent* pOther);
	void OnTriggerExit(PhysicsComponent* pOther);

private:
	// Functions & friends
	friend class PeterPepper_Die;
	void Die();
	friend class PeterPepper_KillEnemy;
	void KillEnemy();

	//// Variables
	int m_Lives;
	int m_Score;
	SpriteRenderer* m_pSpriteRenderer;
	PhysicsComponent* m_pPhysics;

	bool m_CanMoveVertically;
	int m_LadderCount;

	// Movement
	float m_MovementSpeed;

	bool m_IsMovingLeft;
	bool m_IsMovingRight;
	bool m_IsMovingUp;
	bool m_IsMovingDown;
};
