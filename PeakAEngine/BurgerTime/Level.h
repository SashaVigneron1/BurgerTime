#pragma once
class LevelCompleter;
class GameObject;
class Transform;
enum class TileType;
class Scene;

class Level
{
public:
	Level(bool isLastLevel = false, bool useJsonFile = false, const std::string& jsonFilePath = "");
	~Level() = default;
	Level(const Level& other) = delete;
	Level(Level&& other) noexcept = delete;
	Level& operator=(const Level& other) = delete;
	Level& operator=(Level&& other) noexcept = delete;

	void Initialize(Scene* scene);

	void Reset();
	glm::vec3 GetRandomPlatformPosition();

private:
	std::vector<TileType> m_TileLayout;
	std::vector<GameObject*> m_pLevelObjs;
	int m_Rows;
	int m_Columns;

	Scene* m_pScene;
	LevelCompleter* m_pLevelCompleter;
	bool m_HasGeneratedCompleter;

	bool m_IsLastLevel;
	bool m_UseJsonFile;
	std::string m_JsonFilePath;
};

