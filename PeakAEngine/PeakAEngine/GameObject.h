#pragma once
#include <set>
#include <vector>

#include "InputManager.h"
#include "Transform.h"


class Command;
class Scene;
class Component;
class Transform;
class RenderComponent;

class GameObject final
{
public:
	GameObject(Scene* pScene, const glm::vec3& position = glm::vec3());
	~GameObject();
	GameObject(const GameObject& other) = delete;
	GameObject(GameObject&& other) = delete;
	GameObject& operator=(const GameObject& other) = delete;
	GameObject& operator=(GameObject&& other) = delete;

	// Components
	template<typename T> inline T* GetComponent() const;
	template<typename T> void RemoveComponent();
	template<typename T>
	std::enable_if_t<std::is_base_of_v<Component, T>, T*>
	AddComponent(T* component);

	// Updates & Drawing
	void Destroy();
	void Update();
	void FixedUpdate();
	void Render() const;

	// Scenegraphs
	void SetActive(bool value) { m_IsActive = value; }
	void SetParent(GameObject* parent, bool keepWorldPosition = false);
	GameObject* GetParent() const { return m_pParentObj; }

	size_t GetChildCount() const { return m_pChildren.size(); }
	GameObject* GetChildAt(int index) const;

	// Other
	Transform* GetTransform() const { return m_pTransform; }
	void Translate(float x, float y, float z) { m_pTransform->Translate(x, y, z); SetPositionDirty(); }
	void SetWorldPosition(const float x, const float y) { m_pTransform->SetWorldPosition(x, y, 0); SetPositionDirty(); }
	void SetLocalPosition(const float x, const float y) { m_pTransform->SetLocalPosition(x, y, 0); SetPositionDirty(); }
	void SetWorldPosition(const glm::fvec3& pos) { m_pTransform->SetWorldPosition(pos); SetPositionDirty(); }
	void SetLocalPosition(const glm::fvec3& pos) { m_pTransform->SetLocalPosition(pos); SetPositionDirty(); }
	glm::fvec3 GetWorldPosition();
	glm::fvec3 GetLocalPosition();
	void SetPositionDirty();

	void OnGUI();

	void AddTag(const std::string& tag) { m_Tags.insert(tag); }
	bool HasTag(const std::string& tag) { return m_Tags.contains(tag); }

	void AddCommand(ControllerButton button, Command* pCommand, int controllerIndex = 0) { InputManager::GetInstance().AddCommand(button, pCommand, controllerIndex);  m_pCommands.push_back(pCommand); }
	void AddCommand(char sdlKey, Command* pCommand) { InputManager::GetInstance().AddCommand(sdlKey, pCommand), m_pCommands.push_back(pCommand); }
	void DestroyCommands();

	Scene* GetScene() { return m_pScene; }
private:
	//// Functions
	void UpdateWorldPosition();

	// Scenegraphs
	void RemoveChild(GameObject* pChild);
	void AddChild(GameObject* pChild) { m_pChildren.push_back(pChild); }

	//// Variables
	bool m_IsActive;
	bool m_PositionIsDirty;

	Transform* m_pTransform;
	std::vector<Component*> m_pComponents;

	GameObject* m_pParentObj;
	std::vector<GameObject*> m_pChildren;

	std::vector<Command*> m_pCommands;

	std::set<std::string> m_Tags;

	Scene* m_pScene;
};



template <typename  T>
inline T* GameObject::GetComponent() const
{
	T* pComp{ nullptr };

	for (size_t idx{}; idx < m_pComponents.size() && !pComp; ++idx)
		pComp = dynamic_cast<T*>(m_pComponents[idx]);

	return pComp;
}

template <typename T>
void GameObject::RemoveComponent()
{
	for (auto baseComp : m_pComponents)
	{
		T* component = dynamic_cast<T*>(baseComp);
		if (component)
		{
			delete component;
			component = nullptr;

			// Switch last element with this nullptr, and pop back pointer;
			component = m_pComponents.back();
			m_pComponents.pop_back();
		}
	}
	return nullptr;
}

template <typename T>
std::enable_if_t<std::is_base_of_v<Component, T>, T*>
GameObject::AddComponent(T* component)
{
	m_pComponents.push_back(component);
	return component;
}




