#include "pch.h"
#include "Level.h"

#include "BurgerTime.h"
#include "Prefabs.h"
#include "Tile.h"

Level::Level()
	: m_Columns{8}
	, m_Rows{8}
{
}

void Level::Initialize(Scene* scene)
{
	const float tileSize = 80.0f;
	const glm::vec2 topLeft = { BurgerTime::WindowWidth() / 2 - tileSize * m_Columns/2
								,BurgerTime::WindowHeight() / 2 - tileSize * m_Rows/2};

	m_TileTypes =
	{
		TileType::Ladder, TileType::Empty, TileType::Empty, TileType::Ladder, TileType::Empty, TileType::Empty, TileType::Empty, TileType::Empty,
		TileType::Ladder, TileType::Empty, TileType::Empty, TileType::Ladder, TileType::Empty, TileType::Empty, TileType::Empty, TileType::Empty,
		TileType::Ladder, TileType::Empty, TileType::Empty, TileType::Ladder, TileType::Empty, TileType::Empty, TileType::Empty, TileType::Empty,
		TileType::Ladder, TileType::Empty, TileType::Empty, TileType::Ladder, TileType::Empty, TileType::Empty, TileType::Empty, TileType::Empty,
		TileType::Ladder, TileType::Empty, TileType::Empty, TileType::Ladder, TileType::Empty, TileType::Empty, TileType::Empty, TileType::Empty,
		TileType::Ladder, TileType::Empty, TileType::Empty, TileType::Ladder, TileType::Empty, TileType::Empty, TileType::Empty, TileType::Empty,
		TileType::Ladder, TileType::Empty, TileType::Empty, TileType::Ladder, TileType::Empty, TileType::Empty, TileType::Empty, TileType::Empty,
		TileType::Platform, TileType::Platform, TileType::Platform, TileType::Platform, TileType::Platform, TileType::Platform, TileType::Platform, TileType::Platform,
	};

	for (int i = 0; i < (int)m_TileTypes.size(); i++)
	{
		const auto tileType = m_TileTypes[i];
		const int column{ i % m_Columns };
		const int row{ i / m_Rows };

		switch (tileType)
		{
		case TileType::Empty:

			break;
		case TileType::Ladder:
			CreateLadder(scene, tileSize, { topLeft.x + tileSize * column, topLeft.y + tileSize * row });
			break;
		case TileType::Platform:
			CreatePlatform(scene, tileSize, { topLeft.x + tileSize * column, topLeft.y + tileSize * row });
			break;
		}
	}

	//CreateLadderCollection(scene, 5, { BurgerTime::WindowWidth() / 2,BurgerTime::WindowHeight() / 2});
}
