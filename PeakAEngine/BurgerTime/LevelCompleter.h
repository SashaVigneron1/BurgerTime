#pragma once
#include "PeakAEngine/BaseComponent.h"

class Level;
class BurgerPiece;

class LevelCompleter final : public Component
{
public:
	LevelCompleter(bool isLastLevel, Level* pLevel, GameObject* pGameObject);
	virtual ~LevelCompleter() override;
	LevelCompleter(const LevelCompleter& other) = delete;
	LevelCompleter(LevelCompleter&& other) noexcept = delete;
	LevelCompleter& operator=(const LevelCompleter& other) = delete;
	LevelCompleter& operator=(LevelCompleter&& other) noexcept = delete;

	void Update() override;
	void FixedUpdate() override {}
	void OnGUI() override {}
	void Render() const override {}

	void AddBurgerPiece(BurgerPiece* pBurgerPiece) { m_pBurgerPieces.push_back(pBurgerPiece); }
	void Reset();
	void ResetLevelNextFrame();
private:
	const bool m_IsLastLevel;
	bool m_ShouldReset;
	bool m_HasReset;
	Level* m_pLevel;
	std::vector<BurgerPiece*> m_pBurgerPieces;
};

