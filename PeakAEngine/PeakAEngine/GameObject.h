#pragma once
#include <set>
#include <vector>
#include "Transform.h"


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
	template<typename T> T* GetComponent() const;
	template<typename T> void RemoveComponent();
	template<typename T>
	std::enable_if_t<std::is_base_of_v<Component, T>, T*>
	AddComponent(T* component);

	// Updates & Drawing
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
	bool hasTag(const std::string& tag) { return m_Tags.contains(tag); }

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

	std::set<std::string> m_Tags;

	Scene* m_pScene;
};



template <typename  T>
T* GameObject::GetComponent() const
{
	for (auto baseComp : m_pComponents)
	{
		T* component = dynamic_cast<T*>(baseComp);
		if (component)
		{
			return component;
		}
	}
	return nullptr;
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




