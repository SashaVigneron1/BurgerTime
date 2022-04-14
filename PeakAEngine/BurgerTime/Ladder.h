#pragma once
#include "PeakAEngine/BaseComponent.h"

class Ladder final : public Component
{
public:
	Ladder(GameObject* pGameObject);
	virtual ~Ladder() override;
	Ladder(const Ladder& other) = delete;
	Ladder(Ladder&& other) noexcept = delete;
	Ladder& operator=(const Ladder& other) = delete;
	Ladder& operator=(Ladder&& other) noexcept = delete;

	void Update() override {}
	void FixedUpdate() override {}
	void OnGUI() override {}
	void Render() const override {}
private:

};

