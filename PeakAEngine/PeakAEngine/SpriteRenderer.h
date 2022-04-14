#pragma once
#include <unordered_map>

#include "Sprite.h"


class SpriteRenderer final : public Component
{
public:
	SpriteRenderer(GameObject* pGameObject);
	virtual ~SpriteRenderer() override = default;
	SpriteRenderer(const SpriteRenderer& other) = delete;
	SpriteRenderer(SpriteRenderer&& other) noexcept = delete;
	SpriteRenderer& operator=(const SpriteRenderer& other) = delete;
	SpriteRenderer& operator=(SpriteRenderer&& other) noexcept = delete;

	void Update() override { if (m_pActiveSprite) m_pActiveSprite->Update(); }
	void FixedUpdate() override {}
	void Render() const override { if (m_pActiveSprite) m_pActiveSprite->Render(); }
	void OnGUI() override {}

	void SetDirection(Direction direction) { if (m_pActiveSprite) m_pActiveSprite->SetDirection(direction); };

	void AddSprite(const std::string& name, Sprite* pSprite) { m_Sprites[name] = pSprite; }
	void SetActiveSprite(const std::string& name) { m_pActiveSprite = m_Sprites[name]; }
private:
	Sprite* m_pActiveSprite;
	std::unordered_map<std::string, Sprite*> m_Sprites;

};

