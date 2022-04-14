#pragma once

class GameObject;

class Component
{
public:
	Component(GameObject* attachedGameObj) : m_pGameObject{attachedGameObj} {}
	virtual ~Component() = default;
	Component(const Component& other) = delete;
	Component(Component&& other) = delete;
	Component& operator=(const Component& other) = delete;
	Component& operator=(Component&& other) = delete;

	virtual void Update() = 0;
	virtual void FixedUpdate() = 0;
	virtual void OnGUI() = 0;
	virtual void Render() const = 0;

	GameObject* GetGameObject() const { return m_pGameObject; }
protected:
	GameObject* m_pGameObject;
private:

};
