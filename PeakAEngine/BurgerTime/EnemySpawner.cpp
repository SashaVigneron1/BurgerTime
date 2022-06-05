#include "pch.h"
#include "EnemySpawner.h"

#include "Level.h"
#include "Prefabs.h"
#include "PeakAEngine/GameObject.h"
#include "PeakAEngine/Logger.h"
#include "PeakAEngine/MathHelpers.h"
#include "PeakAEngine/Time.h"

EnemySpawner::EnemySpawner(Level* pLevel, GameObject* pGameObject)
	: Component{ pGameObject }
	, m_pLevel{ pLevel }
	, m_AccSpawnTime{ 0.0f }
	, m_MinTimeBetweenSpawns{ 5.0f }
	, m_MaxTimeBetweenSpawns{ 10.0f }
	, m_CurrTimeBetweenSpawns{ 0.0f }
{
}

EnemySpawner::~EnemySpawner()
{
}

void EnemySpawner::Update()
{
	m_AccSpawnTime += Time::DeltaTime();
	if (m_AccSpawnTime > m_CurrTimeBetweenSpawns)
	{
		// Spawn Enemy
		auto spawnPos = m_pLevel->GetRandomPlatformPosition();
		CreateEnemy(m_pGameObject->GetScene(), { spawnPos.x, spawnPos.y - 30.0f });

		// Reset Variables
		m_AccSpawnTime = 0.0f;
		m_CurrTimeBetweenSpawns = RandomFloat(m_MinTimeBetweenSpawns, m_MaxTimeBetweenSpawns);
	}
}
