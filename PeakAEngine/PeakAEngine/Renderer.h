#pragma once
#include "Singleton.h"

#include "structs.h"
#include "SDL.h"

#define RENDERER Renderer::GetInstance()

class RenderLayer;
class Texture2D;

class Renderer final : public Singleton<Renderer>
{
	
public:
	void Init(SDL_Window* window);
	void Render() const;
	void Destroy();

	void RenderTexture(const Texture2D& texture, float x, float y, int layerId = 0) const;
	void RenderTexture(const Texture2D& texture, float x, float y, float width, float height, int layerId = 0) const;
	void RenderTexture(const Texture2D& texture, Rectf dstRect, Rectf srcRect = {}, int layerId = 0, bool flipHorizontal = false, bool flipVertical = false) const;

	SDL_Renderer* GetSDLRenderer() const { return m_Renderer; }
	SDL_Window* GetSDLWindow() const { return m_Window; }

	void AddLayer();

private:
	SDL_Renderer* m_Renderer{};
	SDL_Window* m_Window{};

	int m_WindowWidth{};
	int m_WindowHeight{};

	std::vector<RenderLayer*> m_pLayers;
	
};

