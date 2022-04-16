#pragma once

class RenderLayer
{
public:
	RenderLayer(SDL_Texture* pTargetTexture)
		: m_pTargetTexture{ pTargetTexture }
	{}
	~RenderLayer();
	RenderLayer(const RenderLayer& other) = delete;
	RenderLayer(RenderLayer&& other) noexcept = delete;
	RenderLayer& operator=(const RenderLayer& other) = delete;
	RenderLayer& operator=(RenderLayer&& other) noexcept = delete;

	SDL_Texture* GetTargetTexture() const { return m_pTargetTexture; }

private:
	SDL_Texture* m_pTargetTexture;
};

