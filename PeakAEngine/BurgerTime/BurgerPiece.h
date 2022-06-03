#pragma once
#include <vector>

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

	void Notify(Component* pComponent, Event event) override;

private:
	bool m_IsFalling;

	BurgerPieceType m_Type;

	std::vector<BurgerPiecePart*> m_pParts;

	PhysicsComponent* m_pPhysics;

	float m_FallingSpeed;
};

