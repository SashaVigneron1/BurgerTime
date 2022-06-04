#include "pch.h"
#include "Level.h"

#include "BurgerCatcher.h"
#include "BurgerTime.h"
#include "HighScoreCounter.h"
#include "Ladder.h"
#include "LevelCompleter.h"
#include "LivesCounter.h"
#include "PepperCounter.h"
#include "PeterPepper.h"
#include "Platform.h"
#include "Prefabs.h"
#include "ScoreCounter.h"
#include "Tile.h"
#include "PeakAEngine/JsonParser.h"
#include "PeakAEngine/Scene.h"
#include "PeakAEngine/Transform.h"

Level::Level(bool isLastLevel, bool useJsonFile, const std::string& jsonFilePath)
	: m_Columns{ 8 }
	, m_Rows{ 8 }
	, m_HasGeneratedCompleter{ false }
	, m_IsLastLevel{ isLastLevel }
	, m_UseJsonFile{ useJsonFile }
	, m_JsonFilePath{ jsonFilePath }
{
	
}

void Level::Initialize(Scene* scene)
{
	m_pScene = scene;

	if (!m_HasGeneratedCompleter)
	{
		auto levelCompleterObj = scene->Add(new GameObject(scene));
		m_pLevelCompleter = levelCompleterObj->AddComponent(new LevelCompleter(m_IsLastLevel, this, levelCompleterObj));
		m_HasGeneratedCompleter = true;
	}
	

	if (m_UseJsonFile)
	{
		// Load Json Level
		m_TileLayout.clear();

		JsonParser parser{ m_JsonFilePath };
		auto doc = parser.GetDocument();

		for (auto itr = doc->Begin(); itr != doc->End(); ++itr)
		{
			auto& pos = *itr;

			m_Columns = pos["Columns"].GetInt();
			m_Rows = pos["Rows"].GetInt();
			auto& loc = pos["Tiles"];

			for (int i = 0; i < (int)loc.Size(); i++)
			{
				const rapidjson::Value& tileType = loc[i];

				m_TileLayout.push_back((TileType)tileType.GetInt());
			}
		}
	}
	else
	{
		m_Columns = 8;
		m_Rows = 8;

		// Load Predefined Level (Incomplete)
		m_TileLayout =
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
	}

	const float tileSize = 40.0f;
	const glm::vec2 topLeft = { BurgerTime::WindowWidth() / 2 - tileSize * m_Rows / 2 + tileSize / 2
								,BurgerTime::WindowHeight() / 2 - tileSize * m_Columns / 2 + tileSize / 2 };

	std::set<int> burgerCatcherColumns;

	for (int i = 0; i < (int)m_TileLayout.size(); i++)
	{
		const auto tileType = m_TileLayout[i];
		const int column{ i % m_Rows };
		const int row{ i / m_Rows };

		TileType tileAbove = (i > m_Rows) ? m_TileLayout[i - m_Rows] : TileType::Empty;
		TileType tileUnderneath = (i < (int)m_TileLayout.size() - m_Rows) ? m_TileLayout[i + m_Rows] : TileType::Empty;
		TileType tileLeft = (i > 0) ? m_TileLayout[i - 1] : TileType::Empty;

		switch (tileType)
		{
		case TileType::Ladder:
			m_pLevelObjs.push_back(CreateLadder(scene, tileSize, { topLeft.x + tileSize * column, topLeft.y + tileSize * row })->GetGameObject());
			break;
		case TileType::Platform:
			if (tileAbove == TileType::Ladder || tileUnderneath == TileType::Ladder)
				m_pLevelObjs.push_back(CreatePlatform(scene, PlatformType::coupled, tileSize, { topLeft.x + tileSize * column, topLeft.y + tileSize * row }));
			else
				m_pLevelObjs.push_back(CreatePlatform(scene, PlatformType::normal, tileSize, { topLeft.x + tileSize * column, topLeft.y + tileSize * row }));
			break;
		case TileType::PlatformWithLadderUp:
			m_pLevelObjs.push_back(CreateLadder(scene, tileSize, { topLeft.x + tileSize * column, topLeft.y + tileSize * (row - 1) })->GetGameObject());
			m_pLevelObjs.push_back(CreatePlatform(scene, PlatformType::coupled, tileSize, { topLeft.x + tileSize * column, topLeft.y + tileSize * row }));
			break;
		case TileType::PlatformWithLadderDown:
			m_pLevelObjs.push_back(CreateLadder(scene, tileSize, { topLeft.x + tileSize * column, topLeft.y + tileSize * row })->GetGameObject());
			m_pLevelObjs.push_back(CreatePlatform(scene, PlatformType::coupled, tileSize, { topLeft.x + tileSize * column, topLeft.y + tileSize * row }));
			break;
		case TileType::PlatformWithLadderBoth:
			m_pLevelObjs.push_back(CreateLadder(scene, tileSize, { topLeft.x + tileSize * column, topLeft.y + tileSize * (row - 1) })->GetGameObject());
			m_pLevelObjs.push_back(CreateLadder(scene, tileSize, { topLeft.x + tileSize * column, topLeft.y + tileSize * row })->GetGameObject());
			m_pLevelObjs.push_back(CreatePlatform(scene, PlatformType::coupled, tileSize, { topLeft.x + tileSize * column, topLeft.y + tileSize * row }));
			break;
		case TileType::BurgerIngredient:
			if (tileLeft != TileType::BurgerIngredient)
			{
				BurgerPieceType type = BurgerPieceType::Cheese;

				// If is bottom ingredient: Lower Bun
				// Else if top ingredient: Upper Bun
				// Else Random Ingredient

				if (row == m_Columns - 1)
					type = BurgerPieceType::LowerBun;
				else if (row == 0)
					type = BurgerPieceType::UpperBun;
				else
				{
					// Check if lowerbun
					bool isLowerBun = true;
					for (int j{ row+1 }; j < m_Columns; ++j)
					{
						if (m_TileLayout[m_Rows * j + column] == TileType::BurgerIngredient)
						{
							isLowerBun = false;
							break;
						}
					}

					if (isLowerBun)
						type = BurgerPieceType::LowerBun;
					else
					{
						// Check if UpperBun
						bool isTopBun = true;
						for (int j{ 0 }; j < row-1; ++j)
						{
							if (m_TileLayout[m_Rows * j + column] == TileType::BurgerIngredient)
							{
								isTopBun = false;
								break;
							}
						}

						if (isTopBun)
							type = BurgerPieceType::UpperBun;
						else
						{
							// Select Random Ingredient
							type = (BurgerPieceType)(rand() % ((int)BurgerPieceType::LowerBun-1) + 1);
						}
					}
				}

				if (!burgerCatcherColumns.contains(column) && !burgerCatcherColumns.contains(column-1))
				{
					auto catcher = CreateBurgerCatcher(scene, tileSize, { topLeft.x + tileSize * column, topLeft.y + tileSize * m_Rows + 2 });
					catcher->AddObserver(scene->FindObjectOfType<ScoreCounter>());
					burgerCatcherColumns.insert(column);
					m_pLevelObjs.push_back(catcher->GetGameObject());
				}

				auto burgerPiece = CreateBurgerIngredient(scene, type, tileSize, { topLeft.x + tileSize * column, topLeft.y + tileSize * row });
				m_pLevelCompleter->AddBurgerPiece(burgerPiece);
				m_pLevelObjs.push_back(burgerPiece->GetGameObject());
			}

			m_pLevelObjs.push_back(CreatePlatform(scene, PlatformType::normal, tileSize, { topLeft.x + tileSize * column, topLeft.y + tileSize * row }));
			break;
		default:
			// Default case for Empty
			break;
		}
	}

}

void Level::Reset()
{
	// Reset Variables
	m_pScene->FindObjectOfType<ScoreCounter>()->SetScore(0);
	m_pScene->FindObjectOfType<HighScoreCounter>()->Reset();
	m_pScene->FindObjectOfType<LivesCounter>()->SetLives(9);
	m_pScene->FindObjectOfType<PepperCounter>()->SetPepperCount(5);

	// Destroy Level
	for(int i{}; i < m_pLevelObjs.size(); ++i)
	{
		m_pLevelObjs[i]->Destroy();
	}
	m_pLevelObjs.clear();

	// Move Player to Start
	auto player = m_pScene->FindObjectOfType<PeterPepper>()->GetGameObject();
	glm::vec3 startPos = player->GetWorldPosition();
	glm::vec3 endPos{ BurgerTime::WindowWidth() / 2, BurgerTime::WindowHeight() / 2, 0 };
	glm::vec3 newPos = endPos - startPos;
	player->Translate(newPos.x, newPos.y, newPos.z);

	// Spawn Level
	m_pLevelCompleter->Reset();
	Initialize(m_pScene);
}

