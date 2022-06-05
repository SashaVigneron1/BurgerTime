#pragma once
#include "PeakAEngine/BaseComponent.h"
#include "PeakAEngine/Subject.h"

class PepperCounter;
class Level;
class PhysicsComponent;
class SpriteRenderer;

class PeterPepper final : public Component, public Subject
{
public:
	PeterPepper(PepperCounter* pPepperCounter, SpriteRenderer* pSpriteRenderer, PhysicsComponent* pPhysics, GameObject* attachedObj);
	virtual ~PeterPepper() override;
	PeterPepper(const PeterPepper& other) = delete;
	PeterPepper(PeterPepper&& other) = delete;
	PeterPepper& operator=(const PeterPepper& other) = delete;
	PeterPepper& operator=(PeterPepper&& other) = delete;

	void Update() override;
	void FixedUpdate() override;
	void OnGUI() override;
	void Render() const override {}

	void OnTriggerEnter(PhysicsComponent* pOther);
	void OnTriggerExit(PhysicsComponent* pOther);

	void Die();
private:
	// Functions & friends
	friend class PeterPepper_MoveUp;
	void MoveUp() { m_InputUp = true; }
	friend class PeterPepper_MoveDown;
	void MoveDown() { m_InputDown = true; }
	friend class PeterPepper_MoveLeft;
	void MoveLeft() { m_InputLeft = true; }
	friend class PeterPepper_MoveRight;
	void MoveRight() { m_InputRight = true; }
	friend class PeterPepper_SprayPepper;
	void SprayPepper();

	//// Variables
	PepperCounter* m_pPepperCounter;
	SpriteRenderer* m_pSpriteRenderer;
	PhysicsComponent* m_pPhysics;

	bool m_CanMoveVertically;
	int m_LadderCount;

	// Movement
	float m_MovementSpeed;

	bool m_InputLeft;
	bool m_InputRight;
	bool m_InputUp;
	bool m_InputDown;

	bool m_IsMovingLeft;
	bool m_IsMovingRight;
	bool m_IsMovingUp;
	bool m_IsMovingDown;

	glm::vec3 m_SpawnPosition;
};
