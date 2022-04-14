#pragma once
#include "BaseComponent.h"
#include <SDL_pixels.h>

class Font;
class RenderComponent;

class Text final : public Component
{
public: 
	Text(const std::string& textValue, const glm::u8vec3& color, std::shared_ptr<Font> font, GameObject* attachedObj, RenderComponent* pRenderComponent);
	~Text() override;

	Text(const Text& other) = delete;
	Text(Text&& other) = delete;
	Text& operator=(const Text& other) = delete;
	Text& operator=(Text&& other) = delete;

	void Update() override;
	void FixedUpdate() override;
	void OnGUI() override {}
	void Render() const override {}

	void SetText(const std::string& text);
	void SetColor(const glm::u8vec3& color);

private:
	bool m_NeedsToUpdate;
	std::string m_Text;
	std::shared_ptr<Font> m_Font;

	RenderComponent* m_pRenderComponent;

	SDL_Color m_Color;
};

