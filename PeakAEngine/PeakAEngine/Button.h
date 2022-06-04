#pragma once
#include <functional>

#include "BaseComponent.h"
#include "structs.h"

class SpriteRenderer;

class Button final : public Component
{
public:
	Button(const Rectf& rect, SpriteRenderer* spriteRenderer, const std::string& idleButtonSprite, 
		const std::string& hoveringButtonSprite, const std::string& pressedButtonSprite,
		std::function<void()> pExecute, GameObject* go);
	virtual ~Button() override;
	Button(const Button& other) = delete;
	Button(Button&& other) noexcept = delete;
	Button& operator=(const Button& other) = delete;
	Button& operator=(Button&& other) noexcept = delete;

	void Update() override;
	void FixedUpdate() override;
	void OnGUI() override {}
	void Render() const override;

private:
	std::function<void()> m_pExecute;
	SpriteRenderer* m_pSpriteRenderer;
	std::string m_IdleButtonSprite;
	std::string m_HoveringButtonSprite;
	std::string m_PressedButtonSprite;

	Rectf m_Rect;
};

