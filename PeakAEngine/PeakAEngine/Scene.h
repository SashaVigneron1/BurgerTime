#pragma once
#include "SceneManager.h"
#include "PhysicsHandler.h"
#include "GameObject.h"

class Scene
{
	friend Scene& SceneManager::CreateScene(const std::string& name);
public:
	GameObject* Add(GameObject* object);
	void Remove(GameObject* object);

	template<typename T>
	inline T* FindObjectOfType() const
	{
		for (auto obj : m_Objects)
		{
			auto objOfType = obj->GetComponent<T>();
			if (objOfType)
				return objOfType;
		}
		return nullptr;
	}

	void RemoveMarkedObjects();
	void Update();
	void FixedUpdate();
	void Render() const;
	void OnGUI();

	~Scene();
	Scene(const Scene& other) = delete;
	Scene(Scene&& other) = delete;
	Scene& operator=(const Scene& other) = delete;
	Scene& operator=(Scene&& other) = delete;

	const std::string& GetName() const { return m_Name; }
	b2World* GetPhysicsWorld() { return m_pPhysicsHandler->GetPhysicsWorld(); }
	void EnableOnGUI(bool value) { m_EnableOnGUI = value; }
private:
	explicit Scene(const std::string& name);

	std::string m_Name;
	std::vector<GameObject*> m_Objects{};
	std::vector<GameObject*> m_ObjectsToDestroy{};

	static unsigned int m_IdCounter;

	PhysicsHandler* m_pPhysicsHandler;

	bool m_EnableOnGUI;
};

