#pragma once

#include "PeakAEngine/BaseComponent.h"
#include "PeakAEngine/BaseObserver.h"

class PhysicsComponent;
class BurgerPiecePart;

enum class BurgerPieceType
{
	UpperBun = 0,
	Cheese = 1,
	Patty = 2,
	Tomato = 3,
	Salad = 4,
	LowerBun = 5
};

class BurgerPiece final : public Component, public BaseObserver
{
public: 
	BurgerPiece(BurgerPieceType type, float tileSize, PhysicsComponent* physics, GameObject* go);
	virtual ~BurgerPiece() override = default;

	BurgerPiece(const BurgerPiece& other) = delete;
	BurgerPiece(BurgerPiece&& other) noexcept = delete;
	BurgerPiece& operator=(const BurgerPiece& other) = delete;
	BurgerPiece& operator=(BurgerPiece&& other) noexcept = delete;

	void Update() override;
	void FixedUpdate() override;
	void OnGUI() override {}
	void Render() const override {}

	void SetFalling();
	void StopFalling();
	bool IsFalling() const { return m_IsFalling; }

	void Notify(Component* pComponent, Event event) override;
	void SetCollected() { m_IsCollected = true;	}
	bool IsCollected() const { return m_IsCollected; }

	void AddCollectedEnemy() { ++m_CollectedEnemiesCount; }
	int GetCollectedEnemyCount() const { return m_CollectedEnemiesCount; }

private:
	bool m_IsFalling;
	bool m_IsCollected;

	BurgerPieceType m_Type;

	std::vector<BurgerPiecePart*> m_pParts;

	PhysicsComponent* m_pPhysics;

	float m_MinFallingTime;
	float m_AccFallingTime;
	float m_FallingSpeed;

	int m_CollectedEnemiesCount;
};

