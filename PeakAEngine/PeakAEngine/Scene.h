#pragma once
#include "SceneManager.h"

class b2World;
class GameObject;
class Scene
{
	friend Scene& SceneManager::CreateScene(const std::string& name);
public:
	void Add(GameObject* object);

	void Update();
	void FixedUpdate();
	void Render() const;
	void OnGUI();

	~Scene();
	Scene(const Scene& other) = delete;
	Scene(Scene&& other) = delete;
	Scene& operator=(const Scene& other) = delete;
	Scene& operator=(Scene&& other) = delete;

	b2World* GetPhysicsWorld() { return m_pb2World; }
private:
	explicit Scene(const std::string& name);

	std::string m_Name;
	std::vector<GameObject*> m_Objects{};

	static unsigned int m_IdCounter;

	b2World* m_pb2World{};
};

