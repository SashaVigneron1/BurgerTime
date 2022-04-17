#pragma once
#include "SceneManager.h"
#include "PhysicsHandler.h"

class GameObject;
class Scene
{
	friend Scene& SceneManager::CreateScene(const std::string& name);
public:
	GameObject* Add(GameObject* object);
	void Remove(GameObject* object);


	void Update();
	void FixedUpdate();
	void Render() const;
	void OnGUI();

	~Scene();
	Scene(const Scene& other) = delete;
	Scene(Scene&& other) = delete;
	Scene& operator=(const Scene& other) = delete;
	Scene& operator=(Scene&& other) = delete;

	b2World* GetPhysicsWorld() { return m_pPhysicsHandler->GetPhysicsWorld(); }
private:
	explicit Scene(const std::string& name);

	std::string m_Name;
	std::vector<GameObject*> m_Objects{};

	static unsigned int m_IdCounter;

	PhysicsHandler* m_pPhysicsHandler;
};

