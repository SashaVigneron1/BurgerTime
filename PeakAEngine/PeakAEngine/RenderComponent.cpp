#include "PeakAEnginePCH.h"
#include "RenderComponent.h"

#include "ResourceManager.h"
#include "GameObject.h"
#include "Transform.h"
#include "Renderer.h"

RenderComponent::RenderComponent(const std::string& fileName, GameObject* attachedObj)
	: Component{ attachedObj }
	, m_pTexture{ ResourceManager::GetInstance().LoadTexture(fileName) }
{
}
RenderComponent::~RenderComponent()
{

}


void RenderComponent::Update()
{

}

void RenderComponent::FixedUpdate()
{

}

void RenderComponent::Render() const
{
	RENDERER.RenderTexture(*m_pTexture, m_pGameObject->GetWorldPosition().x, m_pGameObject->GetWorldPosition().y);
}

void RenderComponent::SetTexture(const std::string& fileName)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(fileName);
}

