#pragma once
#include "Singleton.h"

class ImGUIManager final : public Singleton<ImGUIManager>
{
public:
	ImGUIManager() = default;
	virtual ~ImGUIManager() override;

	ImGUIManager(const ImGUIManager& other) = delete;
	ImGUIManager(ImGUIManager&& other) noexcept = delete;
	ImGUIManager& operator=(const ImGUIManager& other) = delete;
	ImGUIManager& operator=(ImGUIManager&& other) noexcept = delete;

	void Initialize(SDL_Window* pSDLWindow);
	void InitializeFrame();

private:
	SDL_Window* m_pWindow = nullptr;
};

