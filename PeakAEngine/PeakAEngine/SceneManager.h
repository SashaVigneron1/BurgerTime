#pragma once
#include "Singleton.h"
#include <vector>

class Scene;
class SceneManager final : public Singleton<SceneManager>
{
public:
	Scene& CreateScene(const std::string& name);
	void LoadScene(const std::string& name);

	void Update();
	void FixedUpdate();
	void Render();
	void OnGUI();
private:
	friend class Singleton<SceneManager>;
	SceneManager() = default;
	std::vector<std::shared_ptr<Scene>> m_Scenes;

	Scene* m_pActiveScene;
};
