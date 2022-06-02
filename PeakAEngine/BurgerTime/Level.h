#pragma once
#include <vector>
class Transform;
enum class TileType;
class Scene;

class Level
{
public:
	Level(bool useJsonFile = false, const std::string& jsonFilePath = "");
	~Level() = default;
	Level(const Level& other) = delete;
	Level(Level&& other) noexcept = delete;
	Level& operator=(const Level& other) = delete;
	Level& operator=(Level&& other) noexcept = delete;

	void Initialize(Scene* scene);
	void SnapToGrid(Transform* pTransform);

private:
	std::vector<TileType> m_TileLayout;
	int m_Rows;
	int m_Columns;

	bool m_UseJsonFile;
	std::string m_JsonFilePath;
};

