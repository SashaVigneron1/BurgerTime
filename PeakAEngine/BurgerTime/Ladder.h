#pragma once
#include "PeakAEngine/BaseComponent.h"

enum class LadderType
{
	couplingPiece,
	middlePiece
};

class Ladder final : public Component
{
public:
	Ladder(GameObject* pGameObject, LadderType piece);
	virtual ~Ladder() override;
	Ladder(const Ladder& other) = delete;
	Ladder(Ladder&& other) noexcept = delete;
	Ladder& operator=(const Ladder& other) = delete;
	Ladder& operator=(Ladder&& other) noexcept = delete;

	void Update() override {}
	void FixedUpdate() override {}
	void OnGUI() override {}
	void Render() const override {}

	LadderType GetLadderPiece() const { return m_LadderPiece; }
private:
	LadderType m_LadderPiece;
};

