#include "PeakAEnginePCH.h"
#include "Sprite.h"

#include "Renderer.h"
#include "ResourceManager.h"
#include "GameObject.h"

#include "Texture2D.h"
#include "Time.h"



Sprite::Sprite(const std::string& fileName, const std::vector<SpriteRow>& rows, int nrCols, float frameSec, GameObject* attachedObj)
	: Sprite{ fileName,rows, nrCols, frameSec, 1.f, attachedObj }
{
}
Sprite::Sprite(const std::string& fileName, const std::vector<SpriteRow>& rows, int nrCols, float frameSec, float m_Scale, GameObject* attachedObj)
	: m_pGameObject{ attachedObj }
	, m_pTexture{ ResourceManager::GetInstance().LoadTexture(fileName) }
	, m_Rows{ rows }
	, m_NrCols{ nrCols }
	, m_FrameSec{ frameSec }
	, m_Scale{ m_Scale }
	, m_AccSec{ 0.f }
	, m_ActFrame{ 0 }
	, m_NrRows{0}
	, m_CurrentRow{0}
{
	std::vector<int> indices;
	for(auto row : rows)
	{
		bool foundIndex{ false };
		for(int i : indices)
		{
			if (row.rowId == i) foundIndex = true;
		}

		if (!foundIndex)
		{
			++m_NrRows;
			indices.push_back(row.rowId);
		}
	}

}
Sprite::~Sprite()
{
}

void Sprite::Update()
{
	m_AccSec += Time::DeltaTime();
	if (m_AccSec >= m_FrameSec)
	{
		++m_ActFrame %= m_NrCols;
		m_AccSec = 0;
	}
}
void Sprite::Render() const
{
	Rectf srcRect;
	srcRect.width = m_pTexture->GetWidth() / (float)m_NrCols;
	srcRect.height = m_pTexture->GetHeight() / (float)m_NrRows;
	srcRect.x = m_ActFrame * srcRect.width;
	srcRect.y = m_CurrentRow * srcRect.height;

	Rectf dstRect;
	dstRect.width = srcRect.width * m_Scale;
	dstRect.height = srcRect.height * m_Scale;
	dstRect.x = m_pGameObject->GetWorldPosition().x - dstRect.width / 2;
	dstRect.y = m_pGameObject->GetWorldPosition().y - dstRect.height / 2;

	Renderer::GetInstance().RenderTexture(*m_pTexture, dstRect, srcRect, m_IsInverse);
}

void Sprite::SetTexture(const std::string& fileName)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(fileName);
}
void Sprite::SetDirection(Direction direction)
{
	for(auto spriteRow : m_Rows)
	{
		if (spriteRow.direction == direction)
		{
			if (spriteRow.inverse) m_IsInverse = true;
			else m_IsInverse = false;

			m_CurrentRow = spriteRow.rowId;
			return;
		}
	}
}