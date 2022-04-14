#pragma once
#include "PeakAEngine/BaseComponent.h"


class BurgerPiece final : public Component
{
public: 
	BurgerPiece() = default;
	virtual ~BurgerPiece() override = default;

	BurgerPiece(const BurgerPiece& other) = delete;
	BurgerPiece(BurgerPiece&& other) noexcept = delete;
	BurgerPiece& operator=(const BurgerPiece& other) = delete;
	BurgerPiece& operator=(BurgerPiece&& other) noexcept = delete;

	void Update() override;
	void FixedUpdate() override;
	void OnGUI() override {}
	void Render() const override {}


private:

};

