#pragma once
#include "PeakAEngine/BaseComponent.h"
#include "PeakAEngine/BaseObserver.h"

class BurgerCatcher : public Component, public BaseObserver
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

	void Notify(Component* pComponent, Event event) override;

private:
};

