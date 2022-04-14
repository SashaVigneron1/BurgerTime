#pragma once
#include "PeakAEngine/BaseComponent.h"
#include "PeakAEngine/Subject.h"

class SpriteRenderer;

class PeterPepper final : public Component, public Subject
{
public:
	PeterPepper(SpriteRenderer* pSpriteRenderer, GameObject* attachedObj);
	virtual ~PeterPepper() override;
	PeterPepper(const PeterPepper& other) = delete;
	PeterPepper(PeterPepper&& other) = delete;
	PeterPepper& operator=(const PeterPepper& other) = delete;
	PeterPepper& operator=(PeterPepper&& other) = delete;

	int GetLives() const { return m_Lives; }
	int GetScore() const { return m_Score; }

	void Update() override;
	void FixedUpdate() override;
	void OnGUI() override;
	void Render() const override {}

private:
	// Functions & friends
	friend class PeterPepper_Die;
	void Die();
	friend class PeterPepper_KillEnemy;
	void KillEnemy();

	// Variables
	int m_Lives;
	int m_Score;
	SpriteRenderer* m_pSpriteRenderer;
};
