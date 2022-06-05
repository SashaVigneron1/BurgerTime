#pragma once
#include "PeakAEngine/BaseComponent.h"
#include "PeakAEngine/Subject.h"

class PhysicsComponent;

class BurgerCatcher : public Component, public Subject
{
public:
	BurgerCatcher(GameObject* go);
	~BurgerCatcher() = default;
	BurgerCatcher(const BurgerCatcher& other) = delete;
	BurgerCatcher(BurgerCatcher&& other) noexcept = delete;
	BurgerCatcher& operator=(const BurgerCatcher& other) = delete;
	BurgerCatcher& operator=(BurgerCatcher&& other) noexcept = delete;

	void Update() override;
	void FixedUpdate() override {}
	void OnGUI() override {}
	void Render() const override {}

	void OnTriggerEnter(PhysicsComponent* pOther);
	void OnTriggerExit(PhysicsComponent* pOther);

private:
	int m_StackCount;
	const float m_HeightPerIngredient;
};

