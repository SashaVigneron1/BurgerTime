#include "PeakAEnginePCH.h"
#include "Text.h"

#include <SDL_ttf.h>

#include "Font.h"
#include "Renderer.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "Texture2D.h"

Text::Text(const std::string& textValue, const glm::u8vec3& color, std::shared_ptr<Font> font, GameObject* attachedObj, RenderComponent* pRenderComponent)
	: Component{attachedObj}
	, m_Text{textValue}
	, m_Font{font}
	, m_NeedsToUpdate{ true }
	, m_Color{ color.x, color.y, color.z }
	, m_pRenderComponent{pRenderComponent}
{
	
}

Text::~Text()
{
	
}

void Text::Update()
{
	if (m_NeedsToUpdate)
	{
		const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), m_Color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(RENDERER.GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		auto newTexture = std::make_shared<Texture2D>(texture);
		if (m_pRenderComponent)
		{
			m_pRenderComponent->SetTexture(newTexture);
		}
		m_NeedsToUpdate = false;
	}
}

void Text::FixedUpdate()
{
	
}

void Text::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsToUpdate = true;
}
void Text::SetColor(const glm::u8vec3& color)
{
	m_Color.r = color.x;
	m_Color.g = color.y;
	m_Color.b = color.z;
	m_NeedsToUpdate = true;
}



