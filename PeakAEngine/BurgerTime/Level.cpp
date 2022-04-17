#include "pch.h"
#include "Level.h"

#include "BurgerTime.h"
#include "Ladder.h"
#include "Platform.h"
#include "Prefabs.h"
#include "Tile.h"
#include "PeakAEngine/Transform.h"

Level::Level()
	: m_Columns{ 8 }
	, m_Rows{ 8 }
{
}

void Level::Initialize(Scene* scene)
{
	const float tileSize = 80.0f;
	const glm::vec2 topLeft = { BurgerTime::WindowWidth() / 2 - tileSize * m_Columns / 2 + tileSize/2
								,BurgerTime::WindowHeight() / 2 - tileSize * m_Rows / 2 + tileSize / 2 };

	m_TileTypes =
	{
		TileType::Platform, TileType::Empty, TileType::Empty, TileType::Empty, TileType::Platform, TileType::Empty, TileType::Empty, TileType::Empty,
		TileType::Ladder, TileType::Empty, TileType::Empty, TileType::Empty, TileType::Ladder, TileType::Empty, TileType::Empty, TileType::Empty,
		TileType::Ladder, TileType::Empty, TileType::Empty, TileType::Empty, TileType::Platform, TileType::Platform, TileType::Platform, TileType::Empty,
		TileType::Platform, TileType::Empty, TileType::Empty, TileType::Empty, TileType::Ladder, TileType::Empty, TileType::Empty, TileType::Empty,
		TileType::Ladder, TileType::Empty, TileType::Empty, TileType::Platform, TileType::Platform, TileType::Empty, TileType::Empty, TileType::Empty,
		TileType::Ladder, TileType::Empty, TileType::Empty, TileType::Ladder, TileType::Empty, TileType::Empty, TileType::Empty, TileType::Empty,
		TileType::Ladder, TileType::Empty, TileType::Empty, TileType::Ladder, TileType::Empty, TileType::Empty, TileType::Empty, TileType::Empty,
		TileType::Platform, TileType::Platform, TileType::Platform, TileType::Platform, TileType::Platform, TileType::Platform, TileType::Platform, TileType::Platform,
	};

	for (int i = 0; i < (int)m_TileTypes.size(); i++)
	{
		const auto tileType = m_TileTypes[i];
		const int column{ i % m_Columns };
		const int row{ i / m_Rows };

		TileType tileAbove = (i > m_Columns) ? m_TileTypes[i - m_Columns] : TileType::Empty;
		TileType tileUnderneath = (i < (int)m_TileTypes.size() - m_Columns) ? m_TileTypes[i + m_Columns] : TileType::Empty;

		switch (tileType)
		{
		case TileType::Ladder:

			CreateLadder(scene, tileSize, { topLeft.x + tileSize * column, topLeft.y + tileSize * row });
			if (tileAbove == TileType::Platform)
			{
				CreateLadder(scene, tileSize, { topLeft.x + tileSize * column, topLeft.y + tileSize * (row - 1) });
			}
			break;
		case TileType::Platform:
			if (tileAbove == TileType::Ladder || tileUnderneath == TileType::Ladder)
			{
				CreatePlatform(scene, PlatformType::coupled, tileSize, { topLeft.x + tileSize * column, topLeft.y + tileSize * row });
			}
			else
			{
				CreatePlatform(scene, PlatformType::normal, tileSize, { topLeft.x + tileSize * column, topLeft.y + tileSize * row });
			}
			break;

		default:
			// Default case for Empty
			break;
		}
	}
}

void Level::SnapToGrid(Transform* pTransform)
{
	auto pos = pTransform->GetWorldPosition();

}
