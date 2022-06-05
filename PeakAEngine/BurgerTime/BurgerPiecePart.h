#pragma once
#include "PeakAEngine/BaseComponent.h"
#include "PeakAEngine/Subject.h"

class PhysicsComponent;

class BurgerPiecePart final : public Component, public Subject
{
public:
	BurgerPiecePart(GameObject* go);
	virtual ~BurgerPiecePart() override = default;

	BurgerPiecePart(const BurgerPiecePart& other) = delete;
	BurgerPiecePart(BurgerPiecePart&& other) noexcept = delete;
	BurgerPiecePart& operator=(const BurgerPiecePart& other) = delete;
	BurgerPiecePart& operator=(BurgerPiecePart&& other) noexcept = delete;

	void Update() override;
	void FixedUpdate() override;
	void OnGUI() override {}
	void Render() const override {}

	void OnTriggerEnter(PhysicsComponent* pOther);
	void OnTriggerExit(PhysicsComponent* pOther);

	bool IsDown() const { return m_IsDown; }
	void ResetDownPosition();

private:
	const float m_DownOffset;
	bool m_IsDown;
};
