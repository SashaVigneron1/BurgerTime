#include "PeakAEnginePCH.h"
#include "Button.h"

#include "GameObject.h"
#include "InputManager.h"
#include "Renderer.h"
#include "SpriteRenderer.h"

Button::Button(const Rectf& rect, SpriteRenderer* spriteRenderer, const std::string& idleButtonSprite,
               const std::string& hoveringButtonSprite, const std::string& pressedButtonSprite,
               std::function<void()> pExecute, GameObject* go)
	: Component(go)
	, m_pExecute{pExecute}
	, m_pSpriteRenderer{ spriteRenderer }
	, m_IdleButtonSprite{ idleButtonSprite }
	, m_HoveringButtonSprite{ hoveringButtonSprite }
	, m_PressedButtonSprite{ pressedButtonSprite }
	, m_Rect{ rect }
{

}

Button::~Button()
{

}

void Button::Update()
{
	// Get Data
	const auto mousePos = InputManager::GetInstance().GetMousePosition();
	const auto spritePos = m_pGameObject->GetWorldPosition();

	// Calculate IsHovering
	const float minX = spritePos.x - m_Rect.width / 2;
	const float maxX = spritePos.x + m_Rect.width / 2;
	const float minY = spritePos.y - m_Rect.height / 2;
	const float maxY = spritePos.y + m_Rect.height / 2;

	const bool isHovering = (mousePos.x > minX && mousePos.x < maxX) && (mousePos.y > minY && mousePos.y < maxY);
	const bool isPressed = isHovering && InputManager::GetInstance().GetMouseButtonDown(MouseButton::LMB);
	
	// If is hovering: Change Sprite
	if (isHovering)
	{
		m_pSpriteRenderer->SetActiveSprite(m_HoveringButtonSprite);
	}

	// If not hovering: Change Sprite Back
	if (!isHovering)
		m_pSpriteRenderer->SetActiveSprite(m_IdleButtonSprite);

	// If Pressed: Execute
	if (isPressed)
	{
		m_pSpriteRenderer->SetActiveSprite(m_PressedButtonSprite);
		m_pExecute();
	}
}

void Button::FixedUpdate()
{

}

void Button::Render() const
{
	/*if (Renderer::DrawDebugPhysics)
	{
		Renderer::DrawRect(m_Rect, Color::Red);
	}*/
}
