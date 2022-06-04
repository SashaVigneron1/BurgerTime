#include "PeakAEnginePCH.h"
#include "RenderComponent.h"

#include "ResourceManager.h"
#include "GameObject.h"
#include "Transform.h"
#include "Renderer.h"
#include "Texture2D.h"

RenderComponent::RenderComponent(const std::string& fileName, GameObject* attachedObj, const Vector2f& pivot)
	: Component{ attachedObj }
	, m_pTexture{ (fileName == "") ? nullptr : ResourceManager::GetInstance().LoadTexture(fileName)}
	, m_Pivot{ pivot }
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
	if (m_pTexture) RENDERER.RenderTexture(*m_pTexture, 
		m_pGameObject->GetWorldPosition().x - (m_Pivot.x * m_pTexture.get()->GetWidth()),
		m_pGameObject->GetWorldPosition().y + (m_Pivot.y * m_pTexture.get()->GetHeight()));
}

void RenderComponent::SetTexture(const std::string& fileName)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(fileName);
}

