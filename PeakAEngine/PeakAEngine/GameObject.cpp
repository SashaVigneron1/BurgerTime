#include "PeakAEnginePCH.h"
#include "GameObject.h"

#include "BaseComponent.h"
#include "InputManager.h"
#include "RenderComponent.h"
#include "Scene.h"
#include "Sprite.h"

#include "Transform.h"

GameObject::GameObject(Scene* pScene, const glm::vec3& position)
	: m_pScene{ pScene }
	, m_pParentObj{ nullptr }
	, m_pTransform{ new Transform(position, this) }
	, m_IsActive{ true }
	, m_PositionIsDirty{ false }
{
}

GameObject::~GameObject()
{
	DestroyCommands();
	for (auto baseComp : m_pComponents)
	{
		delete baseComp;
		baseComp = nullptr;
	}
	for (auto child : m_pChildren)
	{
		delete child;
		child = nullptr;
	}
	delete m_pTransform;
}


void GameObject::Destroy()
{
	m_IsMarkedForDestroy = true;
	for (auto child : m_pChildren)
	{
		child->SetMarkedForDestroy();
	}
		
	m_pScene->Remove(this);
}

void GameObject::Update()
{
	if (m_IsActive)
	{
		for (auto baseComp : m_pComponents)
		{
			baseComp->Update();
		}
		for (auto child : m_pChildren)
		{
			child->Update();
		}
	}
}
void GameObject::FixedUpdate()
{
	if (m_IsActive)
	{
		for (auto baseComp : m_pComponents)
		{
			baseComp->FixedUpdate();
		}
		for (auto child : m_pChildren)
		{
			child->FixedUpdate();
		}
	}
}
void GameObject::Render() const
{
	if (m_IsActive)
	{
		for (auto comp : m_pComponents)
		{
			comp->Render();
		}

		for (auto child : m_pChildren)
		{
			child->Render();
		}
	}
}
void GameObject::OnGUI()
{
	if (m_IsActive)
	{
		for (auto baseComp : m_pComponents)
		{
			baseComp->OnGUI();
		}
		for (auto child : m_pChildren)
		{
			child->OnGUI();
		}
	}
}

glm::fvec3 GameObject::GetWorldPosition()
{
	if (m_PositionIsDirty)
		UpdateWorldPosition();
	return m_pTransform->GetWorldPosition();
}
glm::fvec3 GameObject::GetLocalPosition()
{
	if (m_PositionIsDirty)
		UpdateWorldPosition();
	return m_pTransform->GetLocalPosition();
}

void GameObject::SetPositionDirty()
{
	m_PositionIsDirty = true;
	for (auto child : m_pChildren) 
		child->SetPositionDirty();
}

void GameObject::DestroyCommands()
{
	for ( auto command : m_pCommands)
	{
		InputManager::GetInstance().RemoveCommand(command);
	}

}

bool GameObject::IsMarkedForDestroy() const
{
	return m_IsMarkedForDestroy;
}

void GameObject::UpdateWorldPosition()
{
	if (m_PositionIsDirty)
	{
		if (m_pParentObj)
			m_pTransform->SetWorldPosition(m_pParentObj->GetWorldPosition() + m_pTransform->GetLocalPosition());
		else
			m_pTransform->SetWorldPosition(m_pTransform->GetLocalPosition());

		m_PositionIsDirty = false;
	}
}

void GameObject::SetParent(GameObject* parent, bool keepWorldPosition)
{
	if (!parent)
	{
		SetLocalPosition(GetWorldPosition());
	}
	else
	{
		if (keepWorldPosition)
		{
			SetLocalPosition(GetLocalPosition() - parent->GetWorldPosition());
		}
		SetPositionDirty();
	}

	// Remove itself as a child from the previous parent
	if (m_pParentObj) m_pParentObj->RemoveChild(this);

	// Set the new parent & add itself as a child
	m_pParentObj = parent;
	if (m_pParentObj) m_pParentObj->AddChild(this);
}
void GameObject::RemoveChild(GameObject* pChild)
{
	for (size_t i = 0; i < m_pChildren.size(); i++)
	{
		if (m_pChildren[i] == pChild)
		{
			m_pChildren[i] = m_pChildren.back();
			m_pChildren.pop_back();
		}
	}
}
GameObject* GameObject::GetChildAt(int index) const
{
	if ((int)index < (int)
		m_pChildren.size()) return m_pChildren[index];
	else
		return nullptr;
}