#include "PeakAEnginePCH.h"
#include "Renderer.h"

#include "imgui.h"
#include "SceneManager.h"
#include "structs.h"
#include "Texture2D.h"
#include "backends/imgui_impl_opengl2.h"

#include "RenderLayer.h"
#include "ResourceManager.h"

bool Renderer::DrawDebugPhysics = true;

int GetOpenGLDriverIndex()
{
	auto openglIndex = -1;
	const auto driverCount = SDL_GetNumRenderDrivers();
	for (auto i = 0; i < driverCount; i++)
	{
		SDL_RendererInfo info;
		if (!SDL_GetRenderDriverInfo(i, &info))
			if (!strcmp(info.name, "opengl"))
				openglIndex = i;
	}
	return openglIndex;
}

void Renderer::Init(SDL_Window* window)
{
	m_Window = window;
	m_Renderer = SDL_CreateRenderer(window, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED /* | SDL_RENDERER_PRESENTVSYNC*/);
	if (m_Renderer == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}

	// Render Properties
	SDL_SetRenderDrawBlendMode(m_Renderer, SDL_BLENDMODE_NONE);

	SDL_GetWindowSize(window, &m_WindowWidth, &m_WindowHeight);
}

void Renderer::Render() const
{
	// Clear Previous Frame
	SDL_RenderClear(m_Renderer);

	// Clear Previous Frame Of RenderTargets
	for (size_t i = 0; i < m_pLayers.size(); i++)
	{
		SDL_SetRenderDrawColor(m_Renderer, 0,0, 0, 0);
		SDL_SetRenderTarget(m_Renderer, m_pLayers[i]->GetTargetTexture());
		SDL_RenderFillRect(m_Renderer, NULL);
	}

	SceneManager::GetInstance().Render();

	// Render Layers
	for (size_t i = 0; i < m_pLayers.size(); i++)
		SDL_RenderCopy(m_Renderer, m_pLayers[i]->GetTargetTexture(), nullptr, nullptr);

	// ImGui Render
	ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

	// Present
	SDL_RenderPresent(m_Renderer);
}

void Renderer::Destroy()
{
	if (m_Renderer != nullptr)
	{
		SDL_DestroyRenderer(m_Renderer);
		m_Renderer = nullptr;
	}

	for (size_t i = 0; i < m_pLayers.size(); i++)
	{
		delete m_pLayers[i];
	}
}

void Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, int layerId) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = texture.GetWidth();
	dst.h = texture.GetHeight();

	SDL_SetRenderTarget(m_Renderer, m_pLayers[layerId]->GetTargetTexture());
	SDL_RenderCopy(m_Renderer, texture.GetSDLTexture(), nullptr, &dst);
	SDL_SetRenderTarget(m_Renderer, nullptr);
}
void Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height, int layerId) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);

	SDL_SetRenderTarget(m_Renderer, m_pLayers[layerId]->GetTargetTexture());
	SDL_RenderCopy(m_Renderer, texture.GetSDLTexture(), nullptr, &dst);
	SDL_SetRenderTarget(m_Renderer, nullptr);
}
void Renderer::RenderTexture(const Texture2D& texture, Rectf dstRect, Rectf srcRect, int layerId, bool flipHorizontal, bool flipVertical) const
{
	SDL_Rect src{};
	src.x = static_cast<int>(srcRect.x);
	src.y = static_cast<int>(srcRect.y);
	src.w = static_cast<int>(srcRect.width);
	src.h = static_cast<int>(srcRect.height);

	SDL_Rect dst{};
	dst.x = static_cast<int>(dstRect.x);
	dst.y = static_cast<int>(dstRect.y);
	dst.w = static_cast<int>(dstRect.width);
	dst.h = static_cast<int>(dstRect.height);

	SDL_RendererFlip flip = (SDL_RendererFlip)0;
	if (flipVertical)
	{
		flip = (SDL_RendererFlip)(flip | SDL_FLIP_VERTICAL);
	}
	if (flipHorizontal)
	{
		flip = (SDL_RendererFlip)(flip | SDL_FLIP_HORIZONTAL);
	}

	SDL_SetRenderTarget(m_Renderer, m_pLayers[layerId]->GetTargetTexture());
	SDL_RenderCopyEx(m_Renderer, texture.GetSDLTexture(), &src, &dst, 0.0, nullptr, flip);
	SDL_SetRenderTarget(m_Renderer, nullptr);
}

void Renderer::FillRect(const Rectf& rect, const Color4f& color, int layerId) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(rect.x);
	dst.y = static_cast<int>(rect.y);
	dst.w = static_cast<int>(rect.width);
	dst.h = static_cast<int>(rect.height);

	SDL_SetRenderTarget(m_Renderer, m_pLayers[layerId]->GetTargetTexture());
	SDL_SetRenderDrawColor(m_Renderer, Uint8(color.r * 255), Uint8(color.g * 255), Uint8(color.b * 255), Uint8(color.a * 255));
	SDL_RenderFillRect(m_Renderer, &dst);
	SDL_SetRenderDrawColor(m_Renderer, 0,0,0,255);
	SDL_SetRenderTarget(m_Renderer, nullptr);
}

void Renderer::AddLayer()
{
	m_pLayers.push_back(RESOURCEMANAGER.CreateRenderLayer(m_WindowWidth, m_WindowHeight));
}
