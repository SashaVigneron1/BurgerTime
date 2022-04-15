#pragma once
#include <vector>
enum class TileType;
class Scene;

class Level
{
public:
	Level();
	~Level() = default;
	Level(const Level& other) = delete;
	Level(Level&& other) noexcept = delete;
	Level& operator=(const Level& other) = delete;
	Level& operator=(Level&& other) noexcept = delete;

	void Initialize(Scene* scene);

private:
	std::vector<TileType> m_TileTypes;
	int m_Rows;
	int m_Columns;
};

