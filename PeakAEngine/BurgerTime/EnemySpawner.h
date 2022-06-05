#pragma once
#include <vector>
#include "PeakAEngine/BaseComponent.h"

class Level;

class EnemySpawner final : public Component
{
public:
	EnemySpawner(Level* pLevel, GameObject* pGameObject);
	virtual ~EnemySpawner() override;
	EnemySpawner(const EnemySpawner& other) = delete;
	EnemySpawner(EnemySpawner&& other) noexcept = delete;
	EnemySpawner& operator=(const EnemySpawner& other) = delete;
	EnemySpawner& operator=(EnemySpawner&& other) noexcept = delete;

	void Update() override;
	void FixedUpdate() override {}
	void OnGUI() override {}
	void Render() const override {}
private:
	Level* m_pLevel;

	float m_MinTimeBetweenSpawns;
	float m_MaxTimeBetweenSpawns;
	float m_CurrTimeBetweenSpawns;
	float m_AccSpawnTime;
};

